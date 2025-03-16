"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.User = exports.UserStatus = void 0;
const uuid_1 = require("uuid");
var UserStatus;
(function (UserStatus) {
    UserStatus["ACTIVE"] = "ACTIVE";
    UserStatus["INACTIVE"] = "INACTIVE";
})(UserStatus || (exports.UserStatus = UserStatus = {}));
class User {
    constructor(name, email, timezone) {
        this.id = (0, uuid_1.v4)();
        this.name = name;
        this.email = email;
        this.timezone = timezone;
        this.status = UserStatus.ACTIVE;
    }
    deactivate() {
        this.status = UserStatus.INACTIVE;
    }
    activate() {
        this.status = UserStatus.ACTIVE;
    }
    update(name, email, timezone) {
        if (name)
            this.name = name;
        if (email)
            this.email = email;
        if (timezone)
            this.timezone = timezone;
    }
}
exports.User = User;
