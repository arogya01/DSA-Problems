/**
 * Concurrency utilities for the meeting scheduler
 */

/**
 * Simple implementation of a mutex lock for synchronization
 */
export class Mutex {
  private locked: boolean = false;
  private waitQueue: Array<() => void> = [];

  /**
   * Acquire the lock
   * @returns A promise that resolves when the lock is acquired
   */
  async acquire(): Promise<() => void> {
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
      return new Promise<() => void>((resolve) => {
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
  async withLock<T>(fn: () => Promise<T> | T): Promise<T> {
    const release = await this.acquire();
    try {
      return await Promise.resolve(fn());
    } finally {
      release();
    }
  }
}

/**
 * Read-write lock implementation
 * Allows multiple readers or one writer
 */
export class ReadWriteLock {
  private readers: number = 0;
  private writer: boolean = false;
  private readerQueue: Array<() => void> = [];
  private writerQueue: Array<() => void> = [];

  /**
   * Acquire a read lock
   * @returns A function to release the lock
   */
  async acquireReader(): Promise<() => void> {
    if (this.writer || this.writerQueue.length > 0) {
      // Writer is active or writers are waiting
      return new Promise<() => void>((resolve) => {
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
  private releaseReader(): void {
    this.readers--;
    this.tryToReleaseNextWaiter();
  }

  /**
   * Acquire a write lock
   * @returns A function to release the lock
   */
  async acquireWriter(): Promise<() => void> {
    if (this.writer || this.readers > 0) {
      // Someone else has the lock
      return new Promise<() => void>((resolve) => {
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
  private releaseWriter(): void {
    this.writer = false;
    this.tryToReleaseNextWaiter();
  }

  /**
   * Try to release the next waiter in the queue
   */
  private tryToReleaseNextWaiter(): void {
    if (this.writerQueue.length > 0 && this.readers === 0 && !this.writer) {
      // Release a waiting writer if no active readers/writers
      const nextWriter = this.writerQueue.shift();
      if (nextWriter) nextWriter();
    } else if (this.writerQueue.length === 0 && !this.writer) {
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
  async withReadLock<T>(fn: () => Promise<T> | T): Promise<T> {
    const release = await this.acquireReader();
    try {
      return await Promise.resolve(fn());
    } finally {
      release();
    }
  }

  /**
   * Execute a function with the write lock
   * @param fn The function to execute with the write lock
   * @returns A promise that resolves with the function's result
   */
  async withWriteLock<T>(fn: () => Promise<T> | T): Promise<T> {
    const release = await this.acquireWriter();
    try {
      return await Promise.resolve(fn());
    } finally {
      release();
    }
  }
}

/**
 * A simple delay function using promises
 * @param ms Milliseconds to delay
 * @returns Promise that resolves after the delay
 */
export function delay(ms: number): Promise<void> {
  return new Promise(resolve => setTimeout(resolve, ms));
}

/**
 * Implements a simple async semaphore
 */
export class Semaphore {
  private permits: number;
  private queue: Array<() => void> = [];

  constructor(permits: number) {
    this.permits = permits;
  }

  /**
   * Acquire a permit
   * @returns A function to release the permit
   */
  async acquire(): Promise<() => void> {
    if (this.permits > 0) {
      this.permits--;
      return Promise.resolve(() => this.release());
    }

    return new Promise<() => void>((resolve) => {
      this.queue.push(() => {
        this.permits--;
        resolve(() => this.release());
      });
    });
  }

  /**
   * Release a permit
   */
  private release(): void {
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
  async withPermit<T>(fn: () => Promise<T> | T): Promise<T> {
    const release = await this.acquire();
    try {
      return await Promise.resolve(fn());
    } finally {
      release();
    }
  }
} 