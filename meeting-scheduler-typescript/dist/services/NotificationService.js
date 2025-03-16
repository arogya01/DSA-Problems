"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.NotificationService = exports.NotificationType = void 0;
const ThreadPool_1 = require("../workers/ThreadPool");
/**
 * Notification types
 */
var NotificationType;
(function (NotificationType) {
    NotificationType["INVITATION"] = "INVITATION";
    NotificationType["UPDATE"] = "UPDATE";
    NotificationType["CANCELLATION"] = "CANCELLATION";
    NotificationType["REMINDER"] = "REMINDER";
})(NotificationType || (exports.NotificationType = NotificationType = {}));
/**
 * Service for sending notifications
 */
class NotificationService {
    /**
     * Creates a new notification service
     * @param numThreads Number of worker threads to use
     */
    constructor(numThreads = 2) {
        this.threadPool = new ThreadPool_1.ThreadPool(numThreads);
    }
    /**
     * Send a notification
     * @param type Notification type
     * @param meeting Meeting
     * @param user User
     */
    async sendNotification(type, meeting, user) {
        try {
            await this.threadPool.executeTask((0, ThreadPool_1.createTask)('sendNotification', async (type, meetingId, meetingTitle, userId, userName, userEmail) => {
                // In a real implementation, this would send an email or other notification
                console.log(`Sending ${type} notification for meeting "${meetingTitle}" (${meetingId}) to ${userName} (${userEmail})`);
                // Simulate notification sending delay
                await new Promise(resolve => setTimeout(resolve, 100));
                return {
                    success: true,
                    timestamp: new Date(),
                };
            }, type, meeting.id, meeting.title, user.id, user.name, user.email));
        }
        catch (error) {
            console.error(`Error sending ${type} notification:`, error);
        }
    }
    /**
     * Send meeting invitations to all participants
     * @param meeting Meeting
     * @param users Map of users by ID
     */
    async sendMeetingInvitations(meeting, users) {
        const tasks = meeting.participants.map(participant => {
            const user = users.get(participant.userId);
            if (!user) {
                return Promise.resolve();
            }
            return this.sendNotification(NotificationType.INVITATION, meeting, user);
        });
        await Promise.all(tasks);
    }
    /**
     * Send meeting updates to all participants
     * @param meeting Meeting
     * @param users Map of users by ID
     */
    async sendMeetingUpdates(meeting, users) {
        const participants = [
            meeting.organizer,
            ...meeting.participants.map(p => p.userId),
        ];
        const tasks = participants.map(userId => {
            const user = users.get(userId);
            if (!user) {
                return Promise.resolve();
            }
            return this.sendNotification(NotificationType.UPDATE, meeting, user);
        });
        await Promise.all(tasks);
    }
    /**
     * Send meeting cancellation notifications to all participants
     * @param meeting Meeting
     * @param users Map of users by ID
     */
    async sendMeetingCancellations(meeting, users) {
        const participants = [
            meeting.organizer,
            ...meeting.participants.map(p => p.userId),
        ];
        const tasks = participants.map(userId => {
            const user = users.get(userId);
            if (!user) {
                return Promise.resolve();
            }
            return this.sendNotification(NotificationType.CANCELLATION, meeting, user);
        });
        await Promise.all(tasks);
    }
    /**
     * Send meeting reminders to all participants
     * @param meeting Meeting
     * @param users Map of users by ID
     * @param minutesBefore Minutes before the meeting to send the reminder
     */
    async sendMeetingReminders(meeting, users, minutesBefore = 15) {
        const participants = [
            meeting.organizer,
            ...meeting.participants.map(p => p.userId),
        ];
        const tasks = participants.map(userId => {
            const user = users.get(userId);
            if (!user) {
                return Promise.resolve();
            }
            return this.sendNotification(NotificationType.REMINDER, meeting, user);
        });
        await Promise.all(tasks);
    }
    /**
     * Schedule meeting reminders
     * @param meeting Meeting
     * @param users Map of users by ID
     * @param minutesBefore Minutes before the meeting to send the reminder
     */
    scheduleReminder(meeting, users, minutesBefore = 15) {
        const reminderTime = new Date(meeting.startTime);
        reminderTime.setMinutes(reminderTime.getMinutes() - minutesBefore);
        const now = new Date();
        const delay = Math.max(0, reminderTime.getTime() - now.getTime());
        return setTimeout(() => {
            this.sendMeetingReminders(meeting, users, minutesBefore).catch(error => {
                console.error('Error sending meeting reminders:', error);
            });
        }, delay);
    }
    /**
     * Clean up resources
     */
    async shutdown() {
        await this.threadPool.terminate();
    }
}
exports.NotificationService = NotificationService;
