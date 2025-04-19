// you've been given an array of promises and you've to either resolve with all the proimses/reject with the first one. 


export function resolveAllPromises(promises){

    const result = new Array(promises.length); 
    let completed = 0; 

    return new Promise((resolve, reject) => {
        // Handle empty array case
        if (promises.length === 0) {
            return resolve([]);
        }

        promises.forEach((promise, index) => {
            Promise.resolve(promise)
                .then(value => {
                    result[index] = value;
                    completed++;
                    
                    // If all promises are resolved, resolve with the result array
                    if (completed === promises.length) {
                        resolve(result);
                    }
                })
                .catch(error => {
                    // If any promise rejects, immediately reject the returned promise
                    reject(error);
                });
        });
    });
}


