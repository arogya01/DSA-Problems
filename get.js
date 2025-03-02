function get(obj, path, defaultValue, options = {}) {
    const { separator = '.' } = options;
    // Handle null/undefined objects
    if (obj == null) {
        return defaultValue;
    }

    // Start with a reference to the original object
    // Note: This is not a copy, just a reference - but that's OK 
    // since we only use it for reading values
    let result = obj;

    // Handle array path
    if (Array.isArray(path)) {
        for (const key of path) {
            // Check if current level is null/undefined
            if (result == null) {
                return defaultValue;
            }
            result = result[key];
        }
        return result === undefined ? defaultValue : result;
    }

    // Handle string path
    if (typeof path !== 'string') {
        return defaultValue;
    }

    // Convert bracket notation to dot notation and split
    // Replace [0] with .0, [1] with .1, etc
    const segments = path.replace(/\[(\w+)\]/g, '.$1')
                        .split(separator)
                        .filter(Boolean); // Remove empty segments

    // Traverse the object
    for (const key of segments) {
        // Check if current level is null/undefined
        if (result == null) {
            return defaultValue;
        }
        result = result[key];
    }

    return result === undefined ? defaultValue : result;
}

// Test cases

const obj = {
    a: {
      b: {
        c: [1,2,3]
      }
    }
  }
 console.log(get(obj, 'a.b.c')) // [1,2,3]
 console.log(get(obj, 'a.b.c.0')) // 1
 console.log(get(obj, 'a.b.c[1]')) // 2
 console.log(get(obj, ['a', 'b', 'c', '2'])) // 3
 console.log(get(obj, 'a.b.c[3]')) // undefined
 console.log(get(obj, 'a.c', 'bfe')) // 'bfe