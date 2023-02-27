var myObj = {
  name: "arogya",
  age: "21",
};

console.log(Object.entries(myObj));

const extractVal = Object.fromEntries(Object.entries(myObj));
console.log(extractVal);

let fave;

({ age: fave } = myObj);

console.log(fave);
