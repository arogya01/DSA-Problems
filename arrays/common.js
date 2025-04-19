
// implmenting basic operations -> map, filter, reduce and others. 
// then jumping hoops, essentially, you've all the knowledge, will also improve on the conceptual topics too. try to study more popular machine coding problems yeah for once. 



Array.prototype.myMap = function(callback){
    if(typeof callback != "function"){
        throw new Error("type of callback is not a function");
    }

    const result = []; 
    // oh so, "this" contains the array
    for(let i = 0; i < this.length; i++){
        result.push(callback(this[i], i, this)); 
    }

    return result; 
}

// if a certain condition is true, then we're pushing the elements, otherwise not right. 
Array.prototype.myFilter = function(callback){

    const output = []; 

    if(typeof callback !== "function"){
        throw new Error("Type of callback is not a function"); 
    }

    for(let i = 0; i < this.length; i++){
        callback(this[i],i,this) ?? output.push(callback(this[i], i, this)); 
    }

    return output; 
}


// reduce has a aesthetic to it. well then, 
// umm, 
/* 
structure of reduce is more like: 
 const arr.reduce((accumalatedValue, )=>{

    }, initialValue); 
*/ 
Array.prototype.myReduce = function(callback, initialValue){

    if(typeof callback !== "function"){
        throw new TypeError("callback is not a function"); 
    }

    let accumulator = initialValue !== undefined ? initialValue : this[0]; 
    let startIndex = initialValue !== undefined ? 0 : 1; 

    for(let i = startIndex; i < this.length; i++){
        accumulator = callback(accumulator, this[i], this); 
    }

    return accumulator; 
    
}


Array.prototype.myEvery = function(callback){
    let areAllPassing; 

    for(let i = 0; i < this.length; i++){
        if(!callback(this[i], i)) return false; 
    }

    return true; 
}

const arr = [1, 2, 3, 4, 5];
  
  // Using myMap
  const doubled = arr.myMap(x => x * 2);
  console.log(doubled); // [2, 4, 6, 8, 10]
  
  // Using myFilter
  const evenNumbers = arr.myFilter(x => x % 2 === 0);
  console.log(evenNumbers); // [2, 4]
  
  // Using myReduce
  const sum = arr.myReduce((acc, curr) => acc + curr, 0);
  console.log(sum); // 15
  
  // Using myEvery
  const allPositive = arr.myEvery(x => x > 0);
  console.log(allPositive); // true