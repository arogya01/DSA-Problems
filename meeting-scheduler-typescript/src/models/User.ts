import { v4 as uuidv4 } from 'uuid';

export enum UserStatus {
  ACTIVE = 'ACTIVE',
  INACTIVE = 'INACTIVE',
}

export class User {
  id: string;
  name: string;
  email: string;
  timezone: string;
  status: UserStatus;

  constructor(name: string, email: string, timezone: string) {
    this.id = uuidv4();
    this.name = name;
    this.email = email;
    this.timezone = timezone;
    this.status = UserStatus.ACTIVE;
  }

  deactivate(): void {
    this.status = UserStatus.INACTIVE;
  }

  activate(): void {
    this.status = UserStatus.ACTIVE;
  }

  update(name?: string, email?: string, timezone?: string): void {
    if (name) this.name = name;
    if (email) this.email = email;
    if (timezone) this.timezone = timezone;
  }
} 