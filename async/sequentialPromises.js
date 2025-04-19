const createAsyncTask = () => {
  const random = Math.floor(Math.random() * 10);
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (random > 5) {
        resolve(random);
      } else {
        reject(random);
      }
    }, random * 50);
  });
};

const tasks = [createAsyncTask, createAsyncTask, createAsyncTask, createAsyncTask, createAsyncTask]; 



async function sequentialExecution(tasks, callback) {
    const result = []; 
    const error = []; 

    for(task of tasks){
        try{
            const output = await task(); 
            result.push(output); 
        }
        catch(err){
            error.push(err);
        }
    }

    callback(result, error); 

}


sequentialExecution(tasks, (result,error)=> console.log(result,error)); 