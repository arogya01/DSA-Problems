"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Meeting = exports.RecurrenceType = exports.MeetingStatus = void 0;
const uuid_1 = require("uuid");
var MeetingStatus;
(function (MeetingStatus) {
    MeetingStatus["SCHEDULED"] = "SCHEDULED";
    MeetingStatus["CANCELED"] = "CANCELED";
    MeetingStatus["COMPLETED"] = "COMPLETED";
})(MeetingStatus || (exports.MeetingStatus = MeetingStatus = {}));
var RecurrenceType;
(function (RecurrenceType) {
    RecurrenceType["NONE"] = "NONE";
    RecurrenceType["DAILY"] = "DAILY";
    RecurrenceType["WEEKLY"] = "WEEKLY";
    RecurrenceType["MONTHLY"] = "MONTHLY";
})(RecurrenceType || (exports.RecurrenceType = RecurrenceType = {}));
class Meeting {
    constructor(title, description, startTime, endTime, organizer, participants, priority = 5, recurrenceType = RecurrenceType.NONE, recurrenceEndDate, location) {
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
        this.id = (0, uuid_1.v4)();
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
    cancel() {
        this.status = MeetingStatus.CANCELED;
    }
    complete() {
        this.status = MeetingStatus.COMPLETED;
    }
    reschedule(newStartTime, newEndTime) {
        if (newEndTime <= newStartTime) {
            throw new Error('End time must be after start time');
        }
        this.startTime = newStartTime;
        this.endTime = newEndTime;
    }
    updateParticipantStatus(userId, status) {
        const participantIndex = this.participants.findIndex(p => p.userId === userId);
        if (participantIndex === -1) {
            throw new Error('User is not a participant of this meeting');
        }
        this.participants[participantIndex].status = status;
    }
    addParticipant(userId, isRequired = true) {
        if (this.participants.some(p => p.userId === userId)) {
            throw new Error('User is already a participant');
        }
        this.participants.push({
            userId,
            status: 'PENDING',
            isRequired,
        });
    }
    removeParticipant(userId) {
        const initialLength = this.participants.length;
        this.participants = this.participants.filter(p => p.userId !== userId);
        if (this.participants.length === initialLength) {
            throw new Error('User is not a participant of this meeting');
        }
    }
}
exports.Meeting = Meeting;
