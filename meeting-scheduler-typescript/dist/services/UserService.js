"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.UserService = void 0;
const User_1 = require("../models/User");
const concurrencyUtils_1 = require("../utils/concurrencyUtils");
/**
 * Service class for managing users
 */
class UserService {
    constructor() {
        this.users = new Map();
        this.lock = new concurrencyUtils_1.ReadWriteLock();
    }
    /**
     * Create a new user
     * @param name User name
     * @param email User email
     * @param timezone User timezone
     * @returns Created user
     */
    async createUser(name, email, timezone) {
        return this.lock.withWriteLock(() => {
            // Check if user with email already exists
            for (const user of this.users.values()) {
                if (user.email === email && user.status === User_1.UserStatus.ACTIVE) {
                    throw new Error(`User with email ${email} already exists`);
                }
            }
            const user = new User_1.User(name, email, timezone);
            this.users.set(user.id, user);
            return user;
        });
    }
    /**
     * Get a user by ID
     * @param userId User ID
     * @returns User or undefined if not found
     */
    async getUserById(userId) {
        return this.lock.withReadLock(() => {
            return this.users.get(userId);
        });
    }
    /**
     * Get a user by email
     * @param email User email
     * @returns User or undefined if not found
     */
    async getUserByEmail(email) {
        return this.lock.withReadLock(() => {
            for (const user of this.users.values()) {
                if (user.email === email && user.status === User_1.UserStatus.ACTIVE) {
                    return user;
                }
            }
            return undefined;
        });
    }
    /**
     * Get all active users
     * @returns List of active users
     */
    async getAllUsers() {
        return this.lock.withReadLock(() => {
            return Array.from(this.users.values()).filter(user => user.status === User_1.UserStatus.ACTIVE);
        });
    }
    /**
     * Update a user
     * @param userId User ID
     * @param name New name (optional)
     * @param email New email (optional)
     * @param timezone New timezone (optional)
     * @returns Updated user or undefined if not found
     */
    async updateUser(userId, name, email, timezone) {
        return this.lock.withWriteLock(() => {
            const user = this.users.get(userId);
            if (!user) {
                return undefined;
            }
            // Check if email is taken by another user
            if (email && email !== user.email) {
                for (const otherUser of this.users.values()) {
                    if (otherUser.id !== userId &&
                        otherUser.email === email &&
                        otherUser.status === User_1.UserStatus.ACTIVE) {
                        throw new Error(`Email ${email} is already in use`);
                    }
                }
            }
            user.update(name, email, timezone);
            return user;
        });
    }
    /**
     * Deactivate a user
     * @param userId User ID
     * @returns Deactivated user or undefined if not found
     */
    async deactivateUser(userId) {
        return this.lock.withWriteLock(() => {
            const user = this.users.get(userId);
            if (!user) {
                return undefined;
            }
            user.deactivate();
            return user;
        });
    }
    /**
     * Activate a user
     * @param userId User ID
     * @returns Activated user or undefined if not found
     */
    async activateUser(userId) {
        return this.lock.withWriteLock(() => {
            const user = this.users.get(userId);
            if (!user) {
                return undefined;
            }
            user.activate();
            return user;
        });
    }
}
exports.UserService = UserService;
