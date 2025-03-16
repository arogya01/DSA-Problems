# Meeting Scheduler TypeScript

A concurrent meeting scheduler application built with TypeScript that handles multithreading and concurrency.

## Functional Requirements

1. **User Management**
   - Create, update, and delete users
   - Each user has a unique ID, name, email, and timezone

2. **Meeting Management**
   - Create, update, and delete meetings
   - Each meeting has a unique ID, title, description, start time, end time, and list of participants
   - Meetings can be recurring or one-time events
   - Meetings have statuses (scheduled, canceled, completed)

3. **Scheduling**
   - Check availability of participants before scheduling
   - Prevent double-booking (overlapping meetings)
   - Handle timezone differences between participants
   - Implement a priority system for resolving scheduling conflicts

4. **Notifications**
   - Send notifications for meeting invitations, updates, and reminders
   - Support different notification methods (simulated in this implementation)

5. **Concurrency**
   - Handle multiple scheduling requests simultaneously
   - Use multithreading to improve performance
   - Implement proper locking mechanisms to prevent race conditions

## Technical Implementation

- Built with TypeScript and Node.js
- Uses the Worker Threads API for multithreading
- Implements various concurrency patterns and synchronization primitives
- Simulates a database using in-memory storage (can be extended to use real databases)

## Getting Started

1. Clone the repository
2. Install dependencies:
   ```
   npm install
   ```
3. Build the project:
   ```
   npm run build
   ```
4. Run the application:
   ```
   npm start
   ```

## Project Structure

- `src/models/` - Data models
- `src/services/` - Business logic and services
- `src/workers/` - Worker thread implementations
- `src/utils/` - Utility functions and helpers
- `src/index.ts` - Application entry point

## Concurrency and Threading Concepts

This project demonstrates several concurrency concepts:

1. **Worker Threads** - Node.js Worker Threads API for true parallelism
2. **Mutex Locks** - Prevent race conditions when accessing shared resources
3. **Thread Pools** - Manage a pool of worker threads for efficient task execution
4. **Message Passing** - Communication between the main thread and worker threads
5. **Atomic Operations** - Thread-safe operations on shared data

## License

ISC 