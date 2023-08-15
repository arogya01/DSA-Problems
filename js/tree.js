// alright, TreeNode is the single node and Tree is the bunch of nodes connected together. 

class TreeNode{
  
    constructor(key = null, value = null ,parent){
        this.key = key; 
        this.value = value; 
        this.parent = parent; 
        this.children = []; 
    }

    get isLeaf(){
        return this.children.length == 0;         
    }

    get hasChildren(){
        return !this.isLeaf; 
    }

}

class Tree {

}