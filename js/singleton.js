let counter = 0; 
let instance; 
class Counter {
 
    constructor() {
        if(instance){
            throw new Error('Use getInstance() method to get the single instance of this class.');
        }
        instance = this;
    }
    
    getInstance() {
        return this 
    }

    getCount() {
        return counter; 
    }

    increment(){
        counter++; 
    }

    decrement(){
        counter--; 
    }
}; 

const counter1 = new Counter();
const counter2 = new Counter();

console.log(counter1.getInstance() === counter2.getInstance()); 