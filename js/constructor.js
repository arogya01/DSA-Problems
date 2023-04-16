function Person(name) {
  this.name = name;
  this.introduceSelf = function () {
    console.log("Hi, I'm " + this.name);
  };
}

const arogya = new Person("Arogya");

arogya.introduceSelf();

console.log(new String());
