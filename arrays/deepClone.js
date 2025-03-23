
function cloneDeep(data, clonedObjects = new WeakMap()) {
    // your code here
    if(data === null || typeof data !== "object"){    
      return data; 
    }
  
    if(clonedObjects.has(data)){
      return clonedObjects.get(data); 
    }
    
    const clone = Array.isArray(data) ? [] : {}; 
  
    clonedObjects.set(data, clone); 
  
    for(const key in data){
      if(data.hasOwnProperty(key)){
        const value = data[key]; 
      if(value instanceof Date){
        clone[key] = new Date(value);       
      }
      else if(value instanceof RegExp){
        clone[key] = new RegExp(value.source, value.flags); 
      }
      else if(typeof value === "object"){
        clone[key] = cloneDeep(value,clonedObjects); 
      }
      else{
        //direct copy for primitive values. 
        clone[key] = value; 
      }
  
      }
  
      const symbols = Object.getOwnPropertySymbols(data); 
      console.log('symbols',symbols);
      for(const sym of symbols){
        const value = data[sym]; 
  
        if(value instanceof Data){
          clone[sym] = new Date(value); 
        }
        else if(value instanceof RegExp){
          clone[sym] = new RegExp(value.source, value.flags); 
        }
        else if(typeof value === "object" && value != null){
          clone[sym] = cloneDeep(clone, clonedObjects); 
        }
        else{
          clone[sym] = value; 
        }
      }
    }
  
    return clone;
  }
  
  
  const sym = Symbol()
  const obj = {[sym]:'bfe'}
  console.log('sym',sym);
  const clone = cloneDeep(obj)

  console.log(clone); 