import { parentPort, workerData } from 'worker_threads';
import { Task, TaskResponse } from './ThreadPool';

// Worker entry point
if (parentPort) {
  // Listen for messages from the main thread
  parentPort.on('message', async ({ taskId, task }: { taskId: string; task: Task<any> }) => {
    try {
      // Execute the task
      const result = await executeTask(task);
      
      // Send the result back to the main thread
      parentPort?.postMessage({
        taskId,
        result,
      } as TaskResponse<any>);
    } catch (error) {
      // Send the error back to the main thread
      parentPort?.postMessage({
        taskId,
        error,
      } as TaskResponse<any>);
    }
  });
}

/**
 * Execute a task
 * @param task Task to execute
 * @returns Result of the task
 */
async function executeTask<T>(task: Task<T>): Promise<T> {
  const { func, args } = task;
  
  // Convert the string function back to a function
  // This is a bit of a hack, but it works for serializable functions
  const fn = eval(`(${func})`);
  
  // Execute the function with the args
  return fn(...args);
} 