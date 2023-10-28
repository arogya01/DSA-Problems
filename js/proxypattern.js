const obj = {
    name: "arogya", 
    age:42, 
    nationality:"indian"
}; 

// although there're many methods that you can use to create a proxy,
// get and set are the most common ones. 

const personProxy = new Proxy(obj, {
    get: function(target, property) {
         console.log(`the target property is ${target[property]}`);
    }, 
    set: function(target, property, value) {
        console.log(`Changed ${property} from ${obj[property]} to ${value}`);
        target[property] = value; 
    }
});


personProxy.name; 
personProxy.age = 43;

// proxy object is esesentially encapsulating the original object.
