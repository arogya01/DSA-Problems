

// essentially, have to stringify the obj/primitive or what not you're getting in the thing right!> 
// how to cover for cirucular references. 

// see, we can start with the pseudo code and then discuss it with the LLM, if I'm in the right direction or not.. 
/*
- if primitives then it's pretty easy right ?? 
- if obj => array / object / function 
- and then circular refs are like: 
const a = {
  b : 1, 
  c : a ?? 
}
*/ 

function stringify(value){
   if(typeof value !== "object") return `'${value}'`; 

   if(Array.isArray(value)){
      const output = value.forEach((element) => stringify(element)); 
      return `'${output}'`; 
   }

   

}

console.log(' + "arogya" + '); 