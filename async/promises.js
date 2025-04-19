// A Proimse has three states mapped to it -> pending, fullfilled and rejected. 
// we can create a promise and we can reject/resolve a promise
// register reactions with callbacks. 

class ToyPromise{
    _fullfillmentTasks = []; 
    _rejectionTasks = []; 
    _promiseState = 'pending'; 
    _promiseResult = undefined; 

    resolve(value){
        if(this._promiseState !== "pending") return this; 
        this._promiseState = "fullfilled"; 
        this._promiseResult = value; 
        this.clearAndEnqueueTasks(this._fullfillmentTasks); 
        return this; 
    }


    reject(error){  
        if(this._promiseState !== "pending") return this;
        this._promiseState = "rejected"; 
        this._promiseResult = error; 
        this.clearAndEnqueueTasks(this._rejectionTasks); 
        return this; 
    }

    then(onFulfilled, onRejected){
        const fullfillmentTask = () => {
            if(typeof onFulfilled === "function"){
                onFulfilled(this._promiseResult); 
            }            
        }

        const rejectionTask = () => {
            if(typeof onRejected === "function"){
                onRejected(this._promiseResult); 
            }
        }

        switch(this._promiseState){
            case "pending": 
                this._fullfillmentTasks.push(fullfillmentTask); 
                this._rejectionTasks.push(rejectionTask); 
                break; 
            case "fullfilled": 
                addToTaskQueue(fullfillmentTask); 
                break; 
            case "rejected": 
                addToTaskQueue(rejectionTask); 
                break; 
            default: 
                throw new Error();           
        }
        
        return this;
    }

    clearAndEnqueueTasks(tasks){
        this._fullfillmentTasks = undefined; 
        this._rejectionTasks = undefined; 
        tasks.map(addToTaskQueue); 
    }
    
}

function addToTaskQueue(task){
    setTimeout(task, 0); 
}

// Examples of using ToyPromise

// Example 1: Basic resolution
console.log("Example 1: Basic Resolution");
const successPromise = new ToyPromise();
successPromise.then(
  value => console.log("Success:", value),
  error => console.log("Error:", error)
);
successPromise.resolve("Operation completed");

// Example 2: Rejection
console.log("Example 2: Rejection");
const failurePromise = new ToyPromise();
failurePromise.then(
  value => console.log("Success:", value),
  error => console.log("Error:", error)
);
failurePromise.reject("Operation failed");

// Example 3: Chaining then calls
console.log("Example 3: Chaining");
const chainPromise = new ToyPromise();
chainPromise
  .then(value => console.log("First handler:", value))
  .then(value => console.log("Second handler:", value));
chainPromise.resolve("Chained operation");

// Example 4: Register handlers after resolution
console.log("Example 4: Late subscription");
const immediatePromise = new ToyPromise();
immediatePromise.resolve("Already resolved");
immediatePromise.then(value => console.log("Late handler:", value));

// Example 5: Async resolution
console.log("Example 5: Async resolution");
const asyncPromise = new ToyPromise();
asyncPromise.then(value => console.log("Async result:", value));
console.log("Waiting for async operation...");
setTimeout(() => {
  asyncPromise.resolve("Async operation completed");
}, 1000);



