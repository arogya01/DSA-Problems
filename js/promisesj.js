async function example() {
    const promise = new Promise((resolve, reject) => {
      setTimeout(() => {
        reject(new Error("Something went wrong"));
      }, 1000);
    });
  
    // Not using await here, so the error won't be caught by the try-catch block
    await promise.catch(error => {
      console.error("Caught error:", error.message);
    });
  
    // Rest of the function
    console.log("Function finished");
  }
  
  example();
  