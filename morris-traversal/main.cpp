#include <iostream>

using namespace std;
class TreeNode
{

public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value)
    {
        val = value;
        left = nullptr;
        right = nullptr;
    }

    void morrisTraversal(TreeNode *root)
    {
        // will have to inorder predecessor, which essentially boils down to calculating the right most leaft node of the left sub-tree.

        TreeNode *curr = root;

        while (curr)
        {
            if (curr->left == nullptr)
            {
                cout << curr->val << " ";
                curr = curr->right;
            }
            else
            {
                TreeNode *prev = curr->left;
                while (prev->right && prev->right != curr)
                {
                    prev = prev->right;
                }

                if (prev->right == nullptr)
                {
                    prev->right = curr;
                    curr = curr->left;
                }
                else
                {
                    prev->right = nullptr;
                    cout << curr->val << " ";
                    curr = curr->right;
                }
            }
        }
    }
};
// morris traversal is an algorithm which uses neither stack nor recursion to find the inorder traversal of the tree.

int main()
{
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(10);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(20);
    root->right->right = new TreeNode(30);

    root->morrisTraversal(root);
}