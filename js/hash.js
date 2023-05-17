const { createHash, scryptSync, randomBytes } = require("crypto");

function hash(input) {
  return createHash("sha256").update(input).digest("base64"); // sha256 is a hashing algorithm, and spits out a 256 bit hash.
}

console.log(hash("arogya"));

function signup() {
  const salt = randomBytes(16).toString("hex");
  const hashedPassword = scryptSync(hash("arogya"), salt, 64);
}

function login() {}

// a hash by itself is not sufficient, so we use salting to add a random string to the input before hashing it.
