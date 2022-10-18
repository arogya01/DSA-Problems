#include<bits/stdc++.h>

using namespace std; 

struct TreeNode{
    int val; 
    TreeNode* left; 
    TreeNode* right; 
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        invert(root);
        return root; 
        
    }
    
    void invert(TreeNode* root){
        if(!root) return;
        TreeNode* temp; 
        if(root->left && root->right){
            temp = root->left; 
            root->left = root->right; 
            root->right = temp;
        }
    }
};

int main(){
    
    
}