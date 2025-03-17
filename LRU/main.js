

class LRUCache{
    constructor(capacity){
        this.capacity = capacity; 
        this.cache = new Map(); 
    }

    get(key){
        if(!this.cache.get(key)){
            return -1; 
        }

        const value = this.cache.get(key); 
        this.cache.delete(key); 
        this.cache.set(key,value); 
        
        return value; 

    }

    put(key,value){
        if(this.cache.has(key)){
            this.cache.delete(key); 
        }
        
        // if cache size is full, remove the least recently used. 
        if(this.cache.size >= this.capacity){
            const oldestKey = this.cache.keys().next().value; 
            this.cache.delete(oldestKey); 
        }


        this.cache.set(key,value); 
    }
}

// Usage example
const cache = new LRUCache(3); // Create a cache with capacity 3

cache.put(1, 'one');
cache.put(2, 'two');
console.log(cache.get(1));      // Returns 'one'
cache.put(3, 'three');

// Now if we add another item, the least recently used will be removed
// (which is key 2, since we accessed key 1 most recently)
cache.put(4, 'four');
console.log(cache.get(2));      // Returns -1 (not found)

// Let's check the keys we do have
console.log(cache.get(1));      // Returns 'one'
console.log(cache.get(3));      // Returns 'three'
console.log(cache.get(4));      // Returns 'four'