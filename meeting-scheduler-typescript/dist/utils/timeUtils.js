"use strict";
/**
 * Time utility functions for the meeting scheduler
 */
Object.defineProperty(exports, "__esModule", { value: true });
exports.convertTimezone = convertTimezone;
exports.doTimeRangesOverlap = doTimeRangesOverlap;
exports.generateRecurringMeetingDates = generateRecurringMeetingDates;
/**
 * Converts a date from one timezone to another
 * @param date The date to convert
 * @param fromTimezone Source timezone (e.g., 'America/New_York')
 * @param toTimezone Target timezone (e.g., 'Europe/London')
 * @returns Converted date
 */
function convertTimezone(date, fromTimezone, toTimezone) {
    // In a real implementation, we would use a proper timezone library like moment-timezone
    // For this demo, we're simulating timezone conversion with a simplified approach
    // Define timezone offsets (UTC offset in hours)
    const timezoneOffsets = {
        'America/New_York': -5, // EST
        'America/Los_Angeles': -8, // PST
        'Europe/London': 0, // GMT
        'Europe/Paris': 1, // CET
        'Asia/Tokyo': 9, // JST
        'Australia/Sydney': 10, // AEST
        'UTC': 0,
    };
    // Get offsets or throw error if timezones are not recognized
    const fromOffset = timezoneOffsets[fromTimezone];
    const toOffset = timezoneOffsets[toTimezone];
    if (fromOffset === undefined || toOffset === undefined) {
        throw new Error(`Unknown timezone: ${fromOffset === undefined ? fromTimezone : toTimezone}`);
    }
    // Calculate the difference in hours
    const offsetDiff = toOffset - fromOffset;
    // Create a new date with adjusted time
    const convertedDate = new Date(date);
    convertedDate.setHours(date.getHours() + offsetDiff);
    return convertedDate;
}
/**
 * Checks if two time ranges overlap
 * @param start1 Start of first range
 * @param end1 End of first range
 * @param start2 Start of second range
 * @param end2 End of second range
 * @returns True if the ranges overlap, false otherwise
 */
function doTimeRangesOverlap(start1, end1, start2, end2) {
    return start1 < end2 && start2 < end1;
}
/**
 * Generates recurring meeting dates based on a recurrence pattern
 * @param startDate Start date of the first occurrence
 * @param endDate End date of the first occurrence
 * @param recurrenceType Type of recurrence
 * @param recurrenceEndDate End date for the recurrence
 * @returns Array of meeting time ranges (start and end dates)
 */
function generateRecurringMeetingDates(startDate, endDate, recurrenceType, recurrenceEndDate) {
    const meetings = [];
    const meetingDuration = endDate.getTime() - startDate.getTime();
    let currentStart = new Date(startDate);
    while (currentStart <= recurrenceEndDate) {
        const currentEnd = new Date(currentStart.getTime() + meetingDuration);
        meetings.push({ start: new Date(currentStart), end: currentEnd });
        // Calculate next occurrence based on recurrence type
        if (recurrenceType === 'DAILY') {
            currentStart.setDate(currentStart.getDate() + 1);
        }
        else if (recurrenceType === 'WEEKLY') {
            currentStart.setDate(currentStart.getDate() + 7);
        }
        else if (recurrenceType === 'MONTHLY') {
            currentStart.setMonth(currentStart.getMonth() + 1);
        }
        else {
            break; // Unknown recurrence type
        }
    }
    return meetings;
}
