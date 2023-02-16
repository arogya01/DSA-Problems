var myObj = {
  a: 1,
  b: { val: "arogya" },
};

const { a: wtf, b } = myObj;

console.log(wtf, b);

console.log(myObj.hasOwnProperty("a"));
