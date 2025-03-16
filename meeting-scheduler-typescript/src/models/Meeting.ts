import { v4 as uuidv4 } from 'uuid';

export enum MeetingStatus {
  SCHEDULED = 'SCHEDULED',
  CANCELED = 'CANCELED',
  COMPLETED = 'COMPLETED',
}

export enum RecurrenceType {
  NONE = 'NONE',
  DAILY = 'DAILY',
  WEEKLY = 'WEEKLY',
  MONTHLY = 'MONTHLY',
}

export interface MeetingParticipant {
  userId: string;
  status: 'PENDING' | 'ACCEPTED' | 'DECLINED';
  isRequired: boolean;
}

export class Meeting {
  id: string;
  title: string;
  description: string;
  startTime: Date;
  endTime: Date;
  organizer: string; // userId of the organizer
  participants: MeetingParticipant[];
  status: MeetingStatus;
  priority: number; // 1-10, 10 being highest
  recurrenceType: RecurrenceType;
  recurrenceEndDate?: Date; // if recurrenceType is not NONE
  location?: string; // optional location (physical or virtual)

  constructor(
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
  ) {
    // Validate input
    if (endTime <= startTime) {
      throw new Error('End time must be after start time');
    }

    if (priority < 1 || priority > 10) {
      throw new Error('Priority must be between 1 and 10');
    }

    if (recurrenceType !== RecurrenceType.NONE && !recurrenceEndDate) {
      throw new Error('Recurrence end date is required for recurring meetings');
    }

    this.id = uuidv4();
    this.title = title;
    this.description = description;
    this.startTime = startTime;
    this.endTime = endTime;
    this.organizer = organizer;
    this.participants = participants;
    this.status = MeetingStatus.SCHEDULED;
    this.priority = priority;
    this.recurrenceType = recurrenceType;
    this.recurrenceEndDate = recurrenceEndDate;
    this.location = location;
  }

  cancel(): void {
    this.status = MeetingStatus.CANCELED;
  }

  complete(): void {
    this.status = MeetingStatus.COMPLETED;
  }

  reschedule(newStartTime: Date, newEndTime: Date): void {
    if (newEndTime <= newStartTime) {
      throw new Error('End time must be after start time');
    }
    this.startTime = newStartTime;
    this.endTime = newEndTime;
  }

  updateParticipantStatus(userId: string, status: 'ACCEPTED' | 'DECLINED'): void {
    const participantIndex = this.participants.findIndex(p => p.userId === userId);
    if (participantIndex === -1) {
      throw new Error('User is not a participant of this meeting');
    }
    this.participants[participantIndex].status = status;
  }

  addParticipant(userId: string, isRequired: boolean = true): void {
    if (this.participants.some(p => p.userId === userId)) {
      throw new Error('User is already a participant');
    }
    
    this.participants.push({
      userId,
      status: 'PENDING',
      isRequired,
    });
  }

  removeParticipant(userId: string): void {
    const initialLength = this.participants.length;
    this.participants = this.participants.filter(p => p.userId !== userId);
    
    if (this.participants.length === initialLength) {
      throw new Error('User is not a participant of this meeting');
    }
  }
} 