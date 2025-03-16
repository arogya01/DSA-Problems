"use strict";
/**
 * Concurrency utilities for the meeting scheduler
 */
Object.defineProperty(exports, "__esModule", { value: true });
exports.Semaphore = exports.ReadWriteLock = exports.Mutex = void 0;
exports.delay = delay;
/**
 * Simple implementation of a mutex lock for synchronization
 */
class Mutex {
    constructor() {
        this.locked = false;
        this.waitQueue = [];
    }
    /**
     * Acquire the lock
     * @returns A promise that resolves when the lock is acquired
     */
    async acquire() {
        // Define a release function that will be returned
        const release = () => {
            this.locked = false;
            const nextResolver = this.waitQueue.shift();
            if (nextResolver) {
                nextResolver();
            }
        };
        // If the lock is already acquired, wait in the queue
        if (this.locked) {
            return new Promise((resolve) => {
                this.waitQueue.push(() => {
                    this.locked = true;
                    resolve(release);
                });
            });
        }
        // Lock is free, acquire it immediately
        this.locked = true;
        return Promise.resolve(release);
    }
    /**
     * Execute a function with the lock
     * @param fn The function to execute with the lock
     * @returns A promise that resolves with the function's result
     */
    async withLock(fn) {
        const release = await this.acquire();
        try {
            return await Promise.resolve(fn());
        }
        finally {
            release();
        }
    }
}
exports.Mutex = Mutex;
/**
 * Read-write lock implementation
 * Allows multiple readers or one writer
 */
class ReadWriteLock {
    constructor() {
        this.readers = 0;
        this.writer = false;
        this.readerQueue = [];
        this.writerQueue = [];
    }
    /**
     * Acquire a read lock
     * @returns A function to release the lock
     */
    async acquireReader() {
        if (this.writer || this.writerQueue.length > 0) {
            // Writer is active or writers are waiting
            return new Promise((resolve) => {
                this.readerQueue.push(() => {
                    this.readers++;
                    resolve(this.releaseReader.bind(this));
                });
            });
        }
        // No writers, acquire immediately
        this.readers++;
        return Promise.resolve(this.releaseReader.bind(this));
    }
    /**
     * Release a read lock
     */
    releaseReader() {
        this.readers--;
        this.tryToReleaseNextWaiter();
    }
    /**
     * Acquire a write lock
     * @returns A function to release the lock
     */
    async acquireWriter() {
        if (this.writer || this.readers > 0) {
            // Someone else has the lock
            return new Promise((resolve) => {
                this.writerQueue.push(() => {
                    this.writer = true;
                    resolve(this.releaseWriter.bind(this));
                });
            });
        }
        // Lock is free, acquire immediately
        this.writer = true;
        return Promise.resolve(this.releaseWriter.bind(this));
    }
    /**
     * Release a write lock
     */
    releaseWriter() {
        this.writer = false;
        this.tryToReleaseNextWaiter();
    }
    /**
     * Try to release the next waiter in the queue
     */
    tryToReleaseNextWaiter() {
        if (this.writerQueue.length > 0 && this.readers === 0 && !this.writer) {
            // Release a waiting writer if no active readers/writers
            const nextWriter = this.writerQueue.shift();
            if (nextWriter)
                nextWriter();
        }
        else if (this.writerQueue.length === 0 && !this.writer) {
            // Release all waiting readers if no writers
            const currentReaders = [...this.readerQueue];
            this.readerQueue = [];
            for (const reader of currentReaders) {
                reader();
            }
        }
    }
    /**
     * Execute a function with the read lock
     * @param fn The function to execute with the read lock
     * @returns A promise that resolves with the function's result
     */
    async withReadLock(fn) {
        const release = await this.acquireReader();
        try {
            return await Promise.resolve(fn());
        }
        finally {
            release();
        }
    }
    /**
     * Execute a function with the write lock
     * @param fn The function to execute with the write lock
     * @returns A promise that resolves with the function's result
     */
    async withWriteLock(fn) {
        const release = await this.acquireWriter();
        try {
            return await Promise.resolve(fn());
        }
        finally {
            release();
        }
    }
}
exports.ReadWriteLock = ReadWriteLock;
/**
 * A simple delay function using promises
 * @param ms Milliseconds to delay
 * @returns Promise that resolves after the delay
 */
function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
/**
 * Implements a simple async semaphore
 */
class Semaphore {
    constructor(permits) {
        this.queue = [];
        this.permits = permits;
    }
    /**
     * Acquire a permit
     * @returns A function to release the permit
     */
    async acquire() {
        if (this.permits > 0) {
            this.permits--;
            return Promise.resolve(() => this.release());
        }
        return new Promise((resolve) => {
            this.queue.push(() => {
                this.permits--;
                resolve(() => this.release());
            });
        });
    }
    /**
     * Release a permit
     */
    release() {
        this.permits++;
        const next = this.queue.shift();
        if (next) {
            next();
        }
    }
    /**
     * Execute a function with a permit
     * @param fn The function to execute
     * @returns Result of the function
     */
    async withPermit(fn) {
        const release = await this.acquire();
        try {
            return await Promise.resolve(fn());
        }
        finally {
            release();
        }
    }
}
exports.Semaphore = Semaphore;
