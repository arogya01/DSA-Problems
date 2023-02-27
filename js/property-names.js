var myObj = {
  1: "arogya",
  true: "awesome",
  [[myObj]]: "let's see",
};

console.log(myObj["[[myObj]]"]);

anotherObj = {
  [21 * 2 + "x"]: true,
};

console.log(anotherObj["42x"]);
