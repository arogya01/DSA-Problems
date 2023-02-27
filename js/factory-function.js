//factory pattern is a type of creational pattern where in we're trying to spit out a new object as a result of a function call

//this is a factory function

function createCircle(radius) {
  return {
    radius,
    draw: function () {
      console.log("draw");
    },
  };
}

//this is a constructor function

function Circle(radius) {
  this.radius = radius;
  this.draw = function () {
    console.log("draw");
  };
}

// let's consider a array to store employees information

function Developer(name) {
  this.name = name;
  this.type = "Developer";
}

function Tester(name) {
  this.name = name;
  this.type = "Tester";
}

function EmployeeFactory() {
  this.create = (name, type) => {
    switch (type) {
      case 1:
        return new Developer(name);
      case 2:
        return new Tester(name);
    }
  };
}

const employeeFactory = new EmployeeFactory();
const employees = [];

employees.push(employeeFactory.create("arogya", 1));

function spitOut() {
  console.log("hi, I'm", this.name);
}

employees.forEach((employee) => {
  spitOut.call(employee);
});
