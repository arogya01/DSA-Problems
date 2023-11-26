
// This is a JavaScript coding problem from BFE.dev 

// interface OriginData {
//     origin: string
//     lastUsed: number
//     size: number
//     persistent: boolean
//   }
/**
 * @typedef {object} OriginData
 * @property {string} origin
 * @property {number} lastUsed
 * @property {number} size
 * @property {boolean} persistent
 */

class MyLRUStorage  {
    /**
     * @param {number} capacity
     * @param {() => number} getTimestamp
     */
    constructor(capacity, getTimestamp) {
      this.capacity = capacity
      this.getTimestamp = getTimestamp
      const map = new Map(); 
      this.head = {};
      this.tail = {}; 
      this.head.next = this.tail; 
      this.tail.prev = this.head; 
    }
  
    /**
     * @param {string} origin
     * @returns {OriginData | undefined}
     */
    getData(origin) {
        if(this.data.map.has(origin)){
            const node = this.data.map.get(origin); 
            this
        }
    }
  
    /**
     * @param {string} origin
     * @param {number} size
     * @returns {boolean}
     */
    setData(origin, size) {
  
    }
  
    /**
     * @param {string} origin
     * @returns {void}
     */
    clearData(origin) {
  
    }
  
    /**
     * @param {string} origin
     * @returns {void}
     */
    makePersistent(origin) {
  
    }
  }
  
  
  