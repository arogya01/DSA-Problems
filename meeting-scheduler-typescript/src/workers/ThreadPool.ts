import { Worker, isMainThread, parentPort, workerData } from 'worker_threads';
import { EventEmitter } from 'events';
import * as path from 'path';

/**
 * Type definition for tasks that can be executed in the thread pool
 */
export type Task<T> = {
  name: string;
  args: any[];
  func: string; // Serialized function to be executed in the worker
};

/**
 * Type definition for task responses from worker threads
 */
export type TaskResponse<T> = {
  taskId: string;
  result?: T;
  error?: Error;
};

/**
 * A thread pool implementation that manages a set of worker threads
 */
export class ThreadPool extends EventEmitter {
  private workers: Worker[] = [];
  private tasks: Map<string, Task<any>> = new Map();
  private callbacks: Map<string, (error: Error | null, result?: any) => void> = new Map();
  private taskQueue: string[] = [];
  private isProcessing: boolean = false;

  /**
   * Creates a new thread pool
   * @param numThreads Number of worker threads to create
   */
  constructor(private numThreads: number = 4) {
    super();
    this.initialize();
  }

  /**
   * Initialize the thread pool by creating worker threads
   */
  private initialize(): void {
    if (!isMainThread) {
      throw new Error('ThreadPool can only be created in the main thread');
    }

    for (let i = 0; i < this.numThreads; i++) {
      this.createWorker();
    }
  }

  /**
   * Create a worker thread
   */
  private createWorker(): void {
    const worker = new Worker(path.resolve(__dirname, 'worker.js'));
    
    worker.on('message', (response: TaskResponse<any>) => {
      this.handleTaskResponse(response);
    });
    
    worker.on('error', (error) => {
      console.error('Worker error:', error);
      // Recreate the worker if it crashes
      this.workers = this.workers.filter(w => w !== worker);
      this.createWorker();
    });
    
    worker.on('exit', (code) => {
      if (code !== 0) {
        console.error(`Worker exited with code ${code}`);
        // Recreate the worker if it exits abnormally
        this.workers = this.workers.filter(w => w !== worker);
        this.createWorker();
      }
    });
    
    this.workers.push(worker);
  }

  /**
   * Handle task response from a worker thread
   * @param response Task response
   */
  private handleTaskResponse<T>(response: TaskResponse<T>): void {
    const { taskId, result, error } = response;
    const callback = this.callbacks.get(taskId);
    
    if (callback) {
      callback(error || null, result);
      this.callbacks.delete(taskId);
      this.tasks.delete(taskId);
    }
    
    this.processNextTask();
  }

  /**
   * Process the next task in the queue
   */
  private processNextTask(): void {
    if (this.taskQueue.length === 0) {
      this.isProcessing = false;
      return;
    }
    
    const taskId = this.taskQueue.shift();
    if (!taskId) {
      this.isProcessing = false;
      return;
    }
    
    const task = this.tasks.get(taskId);
    if (!task) {
      this.processNextTask();
      return;
    }
    
    // Find an available worker
    const availableWorker = this.workers.find(worker => 
      !worker.threadId || worker.threadId > 0
    );
    
    if (availableWorker) {
      availableWorker.postMessage({ taskId, task });
    } else {
      // If no worker is available, put the task back in the queue
      this.taskQueue.unshift(taskId);
      setTimeout(() => this.processNextTask(), 10);
    }
  }

  /**
   * Start processing tasks in the queue
   */
  private startProcessing(): void {
    if (this.isProcessing) return;
    
    this.isProcessing = true;
    this.processNextTask();
  }

  /**
   * Submit a task to be executed by a worker thread
   * @param task Task to execute
   * @param callback Callback to be called when the task is complete
   * @returns Task ID
   */
  submitTask<T>(
    task: Task<T>,
    callback: (error: Error | null, result?: T) => void
  ): string {
    const taskId = `task_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
    
    this.tasks.set(taskId, task);
    this.callbacks.set(taskId, callback);
    this.taskQueue.push(taskId);
    
    this.startProcessing();
    
    return taskId;
  }

  /**
   * Execute a task and return a promise with the result
   * @param task Task to execute
   * @returns Promise that resolves with the task result
   */
  executeTask<T>(task: Task<T>): Promise<T> {
    return new Promise((resolve, reject) => {
      this.submitTask(task, (error, result) => {
        if (error) {
          reject(error);
        } else {
          resolve(result as T);
        }
      });
    });
  }

  /**
   * Terminate all worker threads
   */
  terminate(): Promise<number[]> {
    return Promise.all(this.workers.map(worker => worker.terminate()));
  }
}

/**
 * Create a single executor task
 * @param name Task name
 * @param func Function to execute
 * @param args Arguments for the function
 * @returns Task object
 */
export function createTask<T>(
  name: string,
  func: (...args: any[]) => T,
  ...args: any[]
): Task<T> {
  return {
    name,
    func: func.toString(),
    args,
  };
} 