const newObj = {};

Object.assign(
  newObj,
  {
    a: 1,
    b: 2,
  },
  {
    yetAnotherProp: 3,
  }
);

console.log(newObj);

//incredibly awesome....
console.log(newObj.toString);
console.log(Object.hasOwn(newObj, toString));
