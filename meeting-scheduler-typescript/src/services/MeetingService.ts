import { Meeting, MeetingParticipant, MeetingStatus, RecurrenceType } from '../models/Meeting';
import { User } from '../models/User';
import { ReadWriteLock, Mutex } from '../utils/concurrencyUtils';
import { doTimeRangesOverlap, generateRecurringMeetingDates, convertTimezone } from '../utils/timeUtils';
import { ThreadPool, createTask } from '../workers/ThreadPool';

/**
 * Service class for managing meetings
 */
export class MeetingService {
  private meetings: Map<string, Meeting> = new Map();
  private lock: ReadWriteLock = new ReadWriteLock();
  private schedulingMutex: Mutex = new Mutex();
  private threadPool: ThreadPool;

  /**
   * Creates a new meeting service
   * @param numThreads Number of worker threads to use
   */
  constructor(numThreads: number = 4) {
    this.threadPool = new ThreadPool(numThreads);
  }

  /**
   * Create a new meeting
   * @param title Meeting title
   * @param description Meeting description
   * @param startTime Start time
   * @param endTime End time
   * @param organizer Organizer user ID
   * @param participants List of participants
   * @param priority Meeting priority
   * @param recurrenceType Recurrence type
   * @param recurrenceEndDate Recurrence end date
   * @param location Meeting location
   * @returns Created meeting
   */
  async createMeeting(
    title: string,
    description: string,
    startTime: Date,
    endTime: Date,
    organizer: string,
    participants: MeetingParticipant[],
    priority: number = 5,
    recurrenceType: RecurrenceType = RecurrenceType.NONE,
    recurrenceEndDate?: Date,
    location?: string
  ): Promise<Meeting> {
    // Use a mutex to ensure only one scheduling operation happens at a time
    return this.schedulingMutex.withLock(async () => {
      // Check for scheduling conflicts
      await this.checkForSchedulingConflicts(
        startTime,
        endTime,
        [organizer, ...participants.map(p => p.userId)],
        recurrenceType,
        recurrenceEndDate,
        priority
      );

      // Create the meeting
      const meeting = new Meeting(
        title,
        description,
        startTime,
        endTime,
        organizer,
        participants,
        priority,
        recurrenceType,
        recurrenceEndDate,
        location
      );

      // Store the meeting
      await this.lock.withWriteLock(() => {
        this.meetings.set(meeting.id, meeting);
      });

      // Send notifications in the background using worker threads
      this.sendMeetingInvitations(meeting);

      return meeting;
    });
  }

  /**
   * Get a meeting by ID
   * @param meetingId Meeting ID
   * @returns Meeting or undefined if not found
   */
  async getMeetingById(meetingId: string): Promise<Meeting | undefined> {
    return this.lock.withReadLock(() => {
      return this.meetings.get(meetingId);
    });
  }

  /**
   * Get all meetings for a user
   * @param userId User ID
   * @returns List of meetings
   */
  async getMeetingsForUser(userId: string): Promise<Meeting[]> {
    return this.lock.withReadLock(() => {
      return Array.from(this.meetings.values()).filter(
        meeting =>
          (meeting.organizer === userId ||
            meeting.participants.some(p => p.userId === userId)) &&
          meeting.status !== MeetingStatus.CANCELED
      );
    });
  }

  /**
   * Get meetings for a user in a time range
   * @param userId User ID
   * @param startTime Start of time range
   * @param endTime End of time range
   * @returns List of meetings
   */
  async getMeetingsForUserInTimeRange(
    userId: string,
    startTime: Date,
    endTime: Date
  ): Promise<Meeting[]> {
    return this.lock.withReadLock(() => {
      return Array.from(this.meetings.values()).filter(
        meeting =>
          (meeting.organizer === userId ||
            meeting.participants.some(p => p.userId === userId)) &&
          meeting.status !== MeetingStatus.CANCELED &&
          doTimeRangesOverlap(meeting.startTime, meeting.endTime, startTime, endTime)
      );
    });
  }

  /**
   * Update a meeting
   * @param meetingId Meeting ID
   * @param title New title (optional)
   * @param description New description (optional)
   * @param location New location (optional)
   * @returns Updated meeting or undefined if not found
   */
  async updateMeeting(
    meetingId: string,
    title?: string,
    description?: string,
    location?: string
  ): Promise<Meeting | undefined> {
    return this.lock.withWriteLock(() => {
      const meeting = this.meetings.get(meetingId);
      if (!meeting) {
        return undefined;
      }

      if (title) meeting.title = title;
      if (description) meeting.description = description;
      if (location !== undefined) meeting.location = location;

      // Send notifications in the background
      this.sendMeetingUpdates(meeting);

      return meeting;
    });
  }

  /**
   * Reschedule a meeting
   * @param meetingId Meeting ID
   * @param newStartTime New start time
   * @param newEndTime New end time
   * @returns Rescheduled meeting or undefined if not found
   */
  async rescheduleMeeting(
    meetingId: string,
    newStartTime: Date,
    newEndTime: Date
  ): Promise<Meeting | undefined> {
    return this.schedulingMutex.withLock(async () => {
      const meeting = await this.lock.withReadLock(() => {
        return this.meetings.get(meetingId);
      });

      if (!meeting) {
        return undefined;
      }

      // Check for scheduling conflicts
      const participants = [
        meeting.organizer,
        ...meeting.participants.map(p => p.userId),
      ];

      await this.checkForSchedulingConflicts(
        newStartTime,
        newEndTime,
        participants,
        meeting.recurrenceType,
        meeting.recurrenceEndDate,
        meeting.priority,
        meetingId // Exclude this meeting from conflict check
      );

      // Update the meeting
      await this.lock.withWriteLock(() => {
        meeting.reschedule(newStartTime, newEndTime);
      });

      // Send notifications in the background
      this.sendMeetingUpdates(meeting);

      return meeting;
    });
  }

  /**
   * Cancel a meeting
   * @param meetingId Meeting ID
   * @returns Canceled meeting or undefined if not found
   */
  async cancelMeeting(meetingId: string): Promise<Meeting | undefined> {
    return this.lock.withWriteLock(() => {
      const meeting = this.meetings.get(meetingId);
      if (!meeting) {
        return undefined;
      }

      meeting.cancel();

      // Send notifications in the background
      this.sendMeetingCancellation(meeting);

      return meeting;
    });
  }

  /**
   * Complete a meeting
   * @param meetingId Meeting ID
   * @returns Completed meeting or undefined if not found
   */
  async completeMeeting(meetingId: string): Promise<Meeting | undefined> {
    return this.lock.withWriteLock(() => {
      const meeting = this.meetings.get(meetingId);
      if (!meeting) {
        return undefined;
      }

      meeting.complete();
      return meeting;
    });
  }

  /**
   * Update a participant's status for a meeting
   * @param meetingId Meeting ID
   * @param userId User ID
   * @param status New status
   * @returns Updated meeting or undefined if not found
   */
  async updateParticipantStatus(
    meetingId: string,
    userId: string,
    status: 'ACCEPTED' | 'DECLINED'
  ): Promise<Meeting | undefined> {
    return this.lock.withWriteLock(() => {
      const meeting = this.meetings.get(meetingId);
      if (!meeting) {
        return undefined;
      }

      meeting.updateParticipantStatus(userId, status);
      return meeting;
    });
  }

  /**
   * Add a participant to a meeting
   * @param meetingId Meeting ID
   * @param userId User ID
   * @param isRequired Whether the participant is required
   * @returns Updated meeting or undefined if not found
   */
  async addParticipant(
    meetingId: string,
    userId: string,
    isRequired: boolean = true
  ): Promise<Meeting | undefined> {
    return this.schedulingMutex.withLock(async () => {
      const meeting = await this.lock.withReadLock(() => {
        return this.meetings.get(meetingId);
      });

      if (!meeting) {
        return undefined;
      }

      // Check if the user is available
      const userMeetings = await this.getMeetingsForUserInTimeRange(
        userId,
        meeting.startTime,
        meeting.endTime
      );

      if (userMeetings.length > 0) {
        // Check if there's a conflict
        const conflictingMeeting = userMeetings.find(
          m => m.priority >= meeting.priority
        );

        if (conflictingMeeting) {
          throw new Error(
            `User has a conflicting meeting with higher or equal priority: ${conflictingMeeting.title}`
          );
        }
      }

      // Add the participant
      await this.lock.withWriteLock(() => {
        meeting.addParticipant(userId, isRequired);
      });

      // Send invitation
      this.sendMeetingInvitation(meeting, userId);

      return meeting;
    });
  }

  /**
   * Remove a participant from a meeting
   * @param meetingId Meeting ID
   * @param userId User ID
   * @returns Updated meeting or undefined if not found
   */
  async removeParticipant(
    meetingId: string,
    userId: string
  ): Promise<Meeting | undefined> {
    return this.lock.withWriteLock(() => {
      const meeting = this.meetings.get(meetingId);
      if (!meeting) {
        return undefined;
      }

      meeting.removeParticipant(userId);
      return meeting;
    });
  }

  /**
   * Check for scheduling conflicts
   * @param startTime Start time
   * @param endTime End time
   * @param participants Participant user IDs
   * @param recurrenceType Recurrence type
   * @param recurrenceEndDate Recurrence end date
   * @param priority Meeting priority
   * @param excludeMeetingId Meeting ID to exclude from conflict check
   */
  private async checkForSchedulingConflicts(
    startTime: Date,
    endTime: Date,
    participants: string[],
    recurrenceType: RecurrenceType,
    recurrenceEndDate?: Date,
    priority: number = 5,
    excludeMeetingId?: string
  ): Promise<void> {
    // For recurring meetings, generate all occurrences
    let occurrences: { start: Date; end: Date }[] = [];
    
    if (recurrenceType !== RecurrenceType.NONE && recurrenceEndDate) {
      occurrences = generateRecurringMeetingDates(
        startTime,
        endTime,
        recurrenceType,
        recurrenceEndDate
      );
    } else {
      occurrences = [{ start: startTime, end: endTime }];
    }

    // Check each occurrence for conflicts
    for (const occurrence of occurrences) {
      // Use worker threads to check conflicts in parallel
      const tasks = participants.map(userId => {
        return this.threadPool.executeTask(
          createTask(
            'checkUserAvailability',
            async (
              userId: string,
              startTime: Date,
              endTime: Date,
              priority: number,
              excludeMeetingId?: string
            ) => {
              // Get all meetings for the user in this time range
              const userMeetings = await this.getMeetingsForUserInTimeRange(
                userId,
                startTime,
                endTime
              );

              // Filter out the excluded meeting
              const conflictingMeetings = userMeetings.filter(
                meeting => !excludeMeetingId || meeting.id !== excludeMeetingId
              );

              // Check if there's a conflict with higher priority
              const higherPriorityConflict = conflictingMeetings.find(
                meeting => meeting.priority > priority
              );

              if (higherPriorityConflict) {
                return {
                  hasConflict: true,
                  conflictingMeeting: higherPriorityConflict,
                };
              }

              return { hasConflict: false };
            },
            userId,
            occurrence.start,
            occurrence.end,
            priority,
            excludeMeetingId
          )
        );
      });

      // Wait for all tasks to complete
      const results = await Promise.all(tasks);

      // Check for conflicts
      const conflicts = results.filter(result => result.hasConflict && result.conflictingMeeting);
      if (conflicts.length > 0) {
        const conflict = conflicts[0];
        throw new Error(
          `Scheduling conflict: ${conflict.conflictingMeeting?.title || 'Unknown meeting'} has higher priority`
        );
      }
    }
  }

  /**
   * Send meeting invitations to all participants
   * @param meeting Meeting
   */
  private sendMeetingInvitations(meeting: Meeting): void {
    // Use worker threads to send invitations in parallel
    for (const participant of meeting.participants) {
      this.sendMeetingInvitation(meeting, participant.userId);
    }
  }

  /**
   * Send a meeting invitation to a participant
   * @param meeting Meeting
   * @param userId User ID
   */
  private sendMeetingInvitation(meeting: Meeting, userId: string): void {
    this.threadPool.executeTask(
      createTask(
        'sendMeetingInvitation',
        async (meetingId: string, userId: string) => {
          // In a real implementation, this would send an email or other notification
          console.log(`Sending meeting invitation for ${meetingId} to user ${userId}`);
          // Simulate some work
          await new Promise(resolve => setTimeout(resolve, 100));
          return true;
        },
        meeting.id,
        userId
      )
    ).catch(error => {
      console.error('Error sending meeting invitation:', error);
    });
  }

  /**
   * Send meeting updates to all participants
   * @param meeting Meeting
   */
  private sendMeetingUpdates(meeting: Meeting): void {
    // Use worker threads to send updates in parallel
    const participants = [meeting.organizer, ...meeting.participants.map(p => p.userId)];
    
    for (const userId of participants) {
      this.threadPool.executeTask(
        createTask(
          'sendMeetingUpdate',
          async (meetingId: string, userId: string) => {
            // In a real implementation, this would send an email or other notification
            console.log(`Sending meeting update for ${meetingId} to user ${userId}`);
            // Simulate some work
            await new Promise(resolve => setTimeout(resolve, 100));
            return true;
          },
          meeting.id,
          userId
        )
      ).catch(error => {
        console.error('Error sending meeting update:', error);
      });
    }
  }

  /**
   * Send meeting cancellation notifications to all participants
   * @param meeting Meeting
   */
  private sendMeetingCancellation(meeting: Meeting): void {
    // Use worker threads to send cancellations in parallel
    const participants = [meeting.organizer, ...meeting.participants.map(p => p.userId)];
    
    for (const userId of participants) {
      this.threadPool.executeTask(
        createTask(
          'sendMeetingCancellation',
          async (meetingId: string, userId: string) => {
            // In a real implementation, this would send an email or other notification
            console.log(`Sending meeting cancellation for ${meetingId} to user ${userId}`);
            // Simulate some work
            await new Promise(resolve => setTimeout(resolve, 100));
            return true;
          },
          meeting.id,
          userId
        )
      ).catch(error => {
        console.error('Error sending meeting cancellation:', error);
      });
    }
  }

  /**
   * Clean up resources
   */
  async shutdown(): Promise<void> {
    await this.threadPool.terminate();
  }
} 