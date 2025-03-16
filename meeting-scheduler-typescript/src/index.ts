import { User, UserStatus } from './models/User';
import { Meeting, MeetingParticipant, MeetingStatus, RecurrenceType } from './models/Meeting';
import { UserService } from './services/UserService';
import { MeetingService } from './services/MeetingService';
import { NotificationService, NotificationType } from './services/NotificationService';

/**
 * Main application class
 */
class MeetingSchedulerApp {
  private userService: UserService;
  private meetingService: MeetingService;
  private notificationService: NotificationService;
  private users: Map<string, User> = new Map();
  private reminders: Map<string, NodeJS.Timeout> = new Map();

  /**
   * Creates a new meeting scheduler application
   */
  constructor() {
    this.userService = new UserService();
    this.meetingService = new MeetingService(4); // 4 worker threads
    this.notificationService = new NotificationService(2); // 2 worker threads
  }

  /**
   * Initialize the application with sample data
   */
  async initialize(): Promise<void> {
    console.log('Initializing Meeting Scheduler App...');

    // Create some users
    const alice = await this.userService.createUser(
      'Alice Smith',
      'alice@example.com',
      'America/New_York'
    );
    this.users.set(alice.id, alice);

    const bob = await this.userService.createUser(
      'Bob Johnson',
      'bob@example.com',
      'America/Los_Angeles'
    );
    this.users.set(bob.id, bob);

    const charlie = await this.userService.createUser(
      'Charlie Brown',
      'charlie@example.com',
      'Europe/London'
    );
    this.users.set(charlie.id, charlie);

    const diana = await this.userService.createUser(
      'Diana Prince',
      'diana@example.com',
      'Asia/Tokyo'
    );
    this.users.set(diana.id, diana);

    console.log('Created users:', await this.userService.getAllUsers());

    // Schedule a meeting
    const participants: MeetingParticipant[] = [
      { userId: bob.id, status: 'PENDING', isRequired: true },
      { userId: charlie.id, status: 'PENDING', isRequired: true },
      { userId: diana.id, status: 'PENDING', isRequired: false },
    ];

    const meetingStartTime = new Date();
    meetingStartTime.setHours(meetingStartTime.getHours() + 1); // 1 hour from now
    
    const meetingEndTime = new Date(meetingStartTime);
    meetingEndTime.setHours(meetingEndTime.getHours() + 1); // 2 hours from now

    try {
      const meeting = await this.meetingService.createMeeting(
        'Project Kickoff',
        'Discuss the new project goals and timeline',
        meetingStartTime,
        meetingEndTime,
        alice.id,
        participants,
        8, // High priority
        RecurrenceType.NONE
      );

      console.log('Created meeting:', meeting);

      // Schedule a reminder for the meeting
      this.scheduleReminder(meeting, 15); // 15 minutes before

      // Simulate a participant accepting the meeting
      setTimeout(async () => {
        try {
          const updatedMeeting = await this.meetingService.updateParticipantStatus(
            meeting.id,
            bob.id,
            'ACCEPTED'
          );
          console.log('Bob accepted the meeting:', updatedMeeting?.id);
        } catch (error) {
          console.error('Error accepting meeting:', error);
        }
      }, 2000);

      // Simulate a participant declining the meeting
      setTimeout(async () => {
        try {
          const updatedMeeting = await this.meetingService.updateParticipantStatus(
            meeting.id,
            diana.id,
            'DECLINED'
          );
          console.log('Diana declined the meeting:', updatedMeeting?.id);
        } catch (error) {
          console.error('Error declining meeting:', error);
        }
      }, 3000);

      // Simulate updating the meeting
      setTimeout(async () => {
        try {
          const updatedMeeting = await this.meetingService.updateMeeting(
            meeting.id,
            'Project Kickoff - Updated',
            'Discuss the new project goals, timeline, and resource allocation',
            'Conference Room A'
          );
          console.log('Updated meeting:', updatedMeeting?.id);
        } catch (error) {
          console.error('Error updating meeting:', error);
        }
      }, 4000);

      // Simulate scheduling a conflicting meeting
      setTimeout(async () => {
        try {
          const conflictingParticipants: MeetingParticipant[] = [
            { userId: bob.id, status: 'PENDING', isRequired: true },
            { userId: charlie.id, status: 'PENDING', isRequired: true },
          ];

          // This should fail due to scheduling conflict
          const conflictingMeeting = await this.meetingService.createMeeting(
            'Conflicting Meeting',
            'This meeting conflicts with the existing one',
            meetingStartTime,
            meetingEndTime,
            alice.id,
            conflictingParticipants,
            5, // Lower priority than the existing meeting
            RecurrenceType.NONE
          );

          console.log('Created conflicting meeting (should not happen):', conflictingMeeting);
        } catch (error: any) {
          console.log('Expected error creating conflicting meeting:', error.message);
        }
      }, 5000);

      // Simulate scheduling a recurring meeting
      setTimeout(async () => {
        try {
          const recurringParticipants: MeetingParticipant[] = [
            { userId: bob.id, status: 'PENDING', isRequired: true },
          ];

          const recurringStartTime = new Date();
          recurringStartTime.setDate(recurringStartTime.getDate() + 1); // Tomorrow
          recurringStartTime.setHours(10, 0, 0, 0); // 10:00 AM
          
          const recurringEndTime = new Date(recurringStartTime);
          recurringEndTime.setHours(11, 0, 0, 0); // 11:00 AM

          const recurrenceEndDate = new Date(recurringStartTime);
          recurrenceEndDate.setDate(recurrenceEndDate.getDate() + 30); // 30 days from now

          const recurringMeeting = await this.meetingService.createMeeting(
            'Weekly Team Sync',
            'Regular team sync meeting',
            recurringStartTime,
            recurringEndTime,
            alice.id,
            recurringParticipants,
            7, // High priority
            RecurrenceType.WEEKLY,
            recurrenceEndDate
          );

          console.log('Created recurring meeting:', recurringMeeting);
        } catch (error) {
          console.error('Error creating recurring meeting:', error);
        }
      }, 6000);

      // Simulate canceling the meeting
      setTimeout(async () => {
        try {
          const canceledMeeting = await this.meetingService.cancelMeeting(meeting.id);
          console.log('Canceled meeting:', canceledMeeting?.id);
          
          // Clear the reminder for the canceled meeting
          this.clearReminder(meeting.id);
        } catch (error) {
          console.error('Error canceling meeting:', error);
        }
      }, 8000);

    } catch (error) {
      console.error('Error creating meeting:', error);
    }
  }

  /**
   * Schedule a reminder for a meeting
   * @param meeting Meeting
   * @param minutesBefore Minutes before the meeting to send the reminder
   */
  private scheduleReminder(meeting: Meeting, minutesBefore: number): void {
    // Clear any existing reminder
    this.clearReminder(meeting.id);
    
    // Schedule a new reminder
    const reminder = this.notificationService.scheduleReminder(
      meeting,
      this.users,
      minutesBefore
    );
    
    this.reminders.set(meeting.id, reminder);
  }

  /**
   * Clear a reminder for a meeting
   * @param meetingId Meeting ID
   */
  private clearReminder(meetingId: string): void {
    const reminder = this.reminders.get(meetingId);
    if (reminder) {
      clearTimeout(reminder);
      this.reminders.delete(meetingId);
    }
  }

  /**
   * Shut down the application
   */
  async shutdown(): Promise<void> {
    console.log('Shutting down Meeting Scheduler App...');
    
    // Clear all reminders
    for (const [meetingId, reminder] of this.reminders.entries()) {
      clearTimeout(reminder);
    }
    this.reminders.clear();
    
    // Shut down services
    await Promise.all([
      this.meetingService.shutdown(),
      this.notificationService.shutdown(),
    ]);
    
    console.log('Meeting Scheduler App shut down successfully');
  }
}

// Create and run the application
const app = new MeetingSchedulerApp();

// Handle process termination
process.on('SIGINT', async () => {
  console.log('\nReceived SIGINT. Shutting down...');
  await app.shutdown();
  process.exit(0);
});

process.on('SIGTERM', async () => {
  console.log('\nReceived SIGTERM. Shutting down...');
  await app.shutdown();
  process.exit(0);
});

// Initialize the application
app.initialize().catch(error => {
  console.error('Error initializing application:', error);
  process.exit(1);
});

// Keep the process running
console.log('Meeting Scheduler App is running. Press Ctrl+C to exit.'); 