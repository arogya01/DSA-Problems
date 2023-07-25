// Define the string
let str = "box-shadow: 0 3px 11px 0 rgba(25, 25, 25, 0.06)";

// Define the regex
const regex = /#([a-fA-F0-9]{3}|[a-fA-F0-9]{6})[ !important]*;|'#([a-fA-F0-9]{3}|[a-fA-F0-9]{6})'|(rgba\(\d{1,3},\s*\d{1,3},\s*\d{1,3}\))|(rgb\(\d{1,3},\s*\d{1,3},\s*\d{1,3}\))/g;

// Use the match method on the string with the regex as the argument
let matches = str.match(regex);

// Log the matches to the console
console.log(matches);