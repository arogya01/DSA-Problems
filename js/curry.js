

// This is a JavaScript coding problem from BFE.dev 

/**
 * @param { (...args: any[]) => any } fn
 * @returns { (...args: any[]) => any }
 */

const join = (a, b, c) => {
    return `${a}_${b}_${c}`
}

function curry(fn) {
    // your code here
    let a, b, c;
    return function outer(a1, b1, c1) {
        // check for a1 , b1 & c1 is present or not

        if (a1 != undefined & b1 != undefined & c1 != undefined) {
            return fn(a1, b1, c1);
        }

        return function inner(a2, b2, c2) {

            if (a1 == undefined) return fn(a2, b2, c2);
            if (b1 == undefined) return fn(a1, a2, b2);
            if (c1 == undefined) return fn(a1, b1, a2);
        }


    }

}

const curriedJoin = curry(join)

console.log(curriedJoin(1, 2, 3)); // '1_2_3'

console.log(curriedJoin(1)(2, 3)); // '1_2_3'

console.log(curriedJoin(1, 2)(3)); // '1_2_3'





// gathering the following requirements 
// 1. return result if all the args are provided 
// 2. if not, then return a fn which expects missing arguments, and return result when all the args are provided, this should also return a curried fn.. 



