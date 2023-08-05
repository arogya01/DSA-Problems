
function createRangeIterator(start ,end , step){
  let current =start; 
  let iterationCount = 0;  

  return {
    next: function(){
        if(current < end){
            const value = current; 
            current += step; 
            iterationCount++; 
            return {
                value, 
                done : false
            }
        }

        return { 
            value : iterationCount , 
            done : true
        }
        
    }
  }
}; 

let iterator = createRangeIterator(0, 10 ,2 ); 

let result = iterator.next();

do{
    result = iterator.next(); 
    console.log(result.value)
}
while(!result.done)


// a generator fn is defined using the fn*{} syntax, 
// right now, I don't know about the right usecase for generators,

// started with learning about iterators and iterables,
// iterables are objects that implement the [Symbol.iterator] method, 
// example of that is an array,
// iterators are objects that implement the next() method,


// a very stupid simple example of generator fn,
// what the heck is this syntax ??? 
const GeneratorFunction = function () {}.constructor

const myGeneratorFn = new GeneratorFunction(`
  yield 'a'
  yield 'b'
  yield 'c'
`)

for (const val of myGeneratorFn()) {
  console.log(val)
}
