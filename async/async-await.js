


// processes that can pause and resume. 

// this is a generator fnnn.... 
// yield is an operator with which the generator can pause itself and then resume whenever it wants to.! 
// 
function* gen(){

} 

// const genObj = gen(); // {used to control the whole process => genObj.next() , genObj.next()}
// you can use generators to implement iterables.

// something like this: 

function *objectEntries(obj){
    const propKeys = Reflect.ownKeys(obj); 

    for(const propKey of propKeys){
        yield [propKey, obj[propKey]]
    }
}

const jane = {first: "Jane", last: "Doe"}; 

// for (const [key,value] of objectEntries(jane)) {
//     console.log(`${key}: ${value}`);
// }

function* genFunc() {
    // (A)
    console.log('First');
    yield; // (B)
    console.log('Second'); // (C)
}

// const genObj = genFunc(); 

function* fibGenerator(){
    yield 1; 
}

const iter2 = fibGenerator(); 
console.log(iter2.next()); te 
console.log(iter2.next());