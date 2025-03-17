

function flat(arr, depth = 1){
    if(depth <= 0){
        return arr.slice(); 
    }
    let output = []; 
    for(let i = 0; i < arr.length; i++){
        if(i in arr){
            if(Array.isArray(arr[i]) && depth > 0){
                let flattened  = flat(arr[i], depth - 1); 

                for(let j = 0; j < flattened.length; j++){
                    output.push(flattened[j]); 
                }
            }
            else{
                output.push(arr[i]); 
            }
        }
    }

    return output;
}

// Basic usage - flatten one level (default)
const nestedArray1 = [1, 2, [3, 4]];
console.log(flat(nestedArray1));
// Expected output: [1, 2, 3, 4]

// Flatten with depth 0 (returns a copy of the original array)
const nestedArray2 = [1, 2, [3, 4]];
console.log(flat(nestedArray2, 0));
// Expected output: [1, 2, [3, 4]]

// Flatten with depth 2
const deeplyNestedArray = [1, 2, [3, 4, [5, 6]]];
console.log(flat(deeplyNestedArray, 2));
// Expected output: [1, 2, 3, 4, 5, 6]

// Flatten with sparse arrays
const sparseArray = [1, , 3, [4, 5]];
console.log(flat(sparseArray));
// Expected output: [1, undefined, 3, 4, 5]

// Flatten with Infinity depth (flattens all nested arrays)
const veryDeepArray = [1, [2, [3, [4, [5]]]]];
console.log(flat(veryDeepArray, Infinity));
// Expected output: [1, 2, 3, 4, 5]
