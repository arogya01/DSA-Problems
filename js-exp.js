// function greeting(msg) {
//   return function who(name) {
//     console.log(`${msg} , ${name}`);
//   };
// }

// var hello = greeting("Hello"); //when this parameter is returned it's reference is assigned to the hello varieable, which in turn is essentially a function.
// var howdy = greeting("Howdy");

// hello("kyle"); //over here, we're calling greeting for a second time.

// hello("samir");

async function fetchCall() {
  try {
    setTimeout(() => {
      return Promise.resolve("hi");
    }, 100);
  } catch (err) {
    console.log(err);
  }
}

async function whatever() {
  const res = await fetchCall();
  console.log(res);
}

whatever();

function counter(step = 1) {
  let count = 0;

  return function increaseCount() {
    count = count + step;
    return count;
  };
}

var incBy1 = counter(1);
var incBy5 = counter(5);

// incBy1();
console.log(incBy5());
console.log(incBy5());
