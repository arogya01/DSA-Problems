#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    bool checkSymmetric(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
        {
            return true;
        }
        else if (left && right)
        {
            if ((checkSymmetric(left->left, right->right->right)) && (checkSymmetric(left->right, right->right->left)) && (left->val == right->val))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return false;

        return checkSymmetric(root->left, root->right);
    }
};

int main()
{
}