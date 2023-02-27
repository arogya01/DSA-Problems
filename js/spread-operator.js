const obj = {
  firstName: undefined,
  lastName: undefined,
};

const names = {
  firstName: "John",
  lastName: "Doe",
};

const newObj = { ...names, ...obj };

console.log(newObj);

const name1 = "";

const [firstName, lastName] = name1.split(" ");

console.log("firstName is:", firstName ?? "John");

[-2, 1, -3, 4, -1, 2, 1, -5, 4];
