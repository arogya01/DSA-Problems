"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || (function () {
    var ownKeys = function(o) {
        ownKeys = Object.getOwnPropertyNames || function (o) {
            var ar = [];
            for (var k in o) if (Object.prototype.hasOwnProperty.call(o, k)) ar[ar.length] = k;
            return ar;
        };
        return ownKeys(o);
    };
    return function (mod) {
        if (mod && mod.__esModule) return mod;
        var result = {};
        if (mod != null) for (var k = ownKeys(mod), i = 0; i < k.length; i++) if (k[i] !== "default") __createBinding(result, mod, k[i]);
        __setModuleDefault(result, mod);
        return result;
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.ThreadPool = void 0;
exports.createTask = createTask;
const worker_threads_1 = require("worker_threads");
const events_1 = require("events");
const path = __importStar(require("path"));
/**
 * A thread pool implementation that manages a set of worker threads
 */
class ThreadPool extends events_1.EventEmitter {
    /**
     * Creates a new thread pool
     * @param numThreads Number of worker threads to create
     */
    constructor(numThreads = 4) {
        super();
        this.numThreads = numThreads;
        this.workers = [];
        this.tasks = new Map();
        this.callbacks = new Map();
        this.taskQueue = [];
        this.isProcessing = false;
        this.initialize();
    }
    /**
     * Initialize the thread pool by creating worker threads
     */
    initialize() {
        if (!worker_threads_1.isMainThread) {
            throw new Error('ThreadPool can only be created in the main thread');
        }
        for (let i = 0; i < this.numThreads; i++) {
            this.createWorker();
        }
    }
    /**
     * Create a worker thread
     */
    createWorker() {
        const worker = new worker_threads_1.Worker(path.resolve(__dirname, 'worker.js'));
        worker.on('message', (response) => {
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
    handleTaskResponse(response) {
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
    processNextTask() {
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
        const availableWorker = this.workers.find(worker => !worker.threadId || worker.threadId > 0);
        if (availableWorker) {
            availableWorker.postMessage({ taskId, task });
        }
        else {
            // If no worker is available, put the task back in the queue
            this.taskQueue.unshift(taskId);
            setTimeout(() => this.processNextTask(), 10);
        }
    }
    /**
     * Start processing tasks in the queue
     */
    startProcessing() {
        if (this.isProcessing)
            return;
        this.isProcessing = true;
        this.processNextTask();
    }
    /**
     * Submit a task to be executed by a worker thread
     * @param task Task to execute
     * @param callback Callback to be called when the task is complete
     * @returns Task ID
     */
    submitTask(task, callback) {
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
    executeTask(task) {
        return new Promise((resolve, reject) => {
            this.submitTask(task, (error, result) => {
                if (error) {
                    reject(error);
                }
                else {
                    resolve(result);
                }
            });
        });
    }
    /**
     * Terminate all worker threads
     */
    terminate() {
        return Promise.all(this.workers.map(worker => worker.terminate()));
    }
}
exports.ThreadPool = ThreadPool;
/**
 * Create a single executor task
 * @param name Task name
 * @param func Function to execute
 * @param args Arguments for the function
 * @returns Task object
 */
function createTask(name, func, ...args) {
    return {
        name,
        func: func.toString(),
        args,
    };
}
