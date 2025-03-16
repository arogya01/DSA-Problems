"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const worker_threads_1 = require("worker_threads");
// Worker entry point
if (worker_threads_1.parentPort) {
    // Listen for messages from the main thread
    worker_threads_1.parentPort.on('message', async ({ taskId, task }) => {
        try {
            // Execute the task
            const result = await executeTask(task);
            // Send the result back to the main thread
            worker_threads_1.parentPort?.postMessage({
                taskId,
                result,
            });
        }
        catch (error) {
            // Send the error back to the main thread
            worker_threads_1.parentPort?.postMessage({
                taskId,
                error,
            });
        }
    });
}
/**
 * Execute a task
 * @param task Task to execute
 * @returns Result of the task
 */
async function executeTask(task) {
    const { func, args } = task;
    // Convert the string function back to a function
    // This is a bit of a hack, but it works for serializable functions
    const fn = eval(`(${func})`);
    // Execute the function with the args
    return fn(...args);
}
