

class Node {
    constructor(value){
        this.data = value; 
        this.next = null; 
        this.prev= null; 
    }
}; 


class DoublyLinkedList{
   
    constructor(){
        this.head = null; 
        this.tail = null; 
    }

    isEmpty(){
        return this.head === null; 
    }
};