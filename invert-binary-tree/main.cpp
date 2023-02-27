#include <iostream>
#include <vector>

using namespace std;

// example of invoking this below struct would be
//
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        invert(root);
        return root;
    }

    void invert(TreeNode *root)
    {
        if (!root)
            return;
        TreeNode *temp;
        if (root->left && root->right)
        {
            temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
    }
};

int main()
{
    TreeNode *root = new TreeNode();
    root->val = 1;
    root->left = new TreeNode();
    root->left->val = 2;
    root->right = new TreeNode();
    root->right->val = 3;
    vector<vector<int>> result{{1, 2, 3}};
    Solution s;
    s.invertTree(root);
    cout << root->left->val;
}