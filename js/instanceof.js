function Person(name, age) {
    this.name = name;
    this.age = age;
  }
  
  Person.prototype[@@hasInstance] = function(object) {
    return object instanceof Person;
  };
  
  var person = new Person("John Doe", 30);
  
  console.log(person instanceof Person); // true
  