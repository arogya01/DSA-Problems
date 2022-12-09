#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left{nullptr}, right{nullptr} {}
    TreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
};

class Solution
{
public:
    void computeLeafNodes(TreeNode *root, vector<int> r)
    {

        if (!root)
            return;

        if (root->left)
            computeLeafNodes(root->left, r);
        if (root->right)
            computeLeafNodes(root->right, r);

        if (!root->left && !root->right)
        {
            r.push_back(root->val);
        }
    }

    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {
        vector<int> r1;
        vector<int> r2;
        computeLeafNodes(root1, r1);
        computeLeafNodes(root2, r2);

        return r1 == r2;
    }
};

int main()
{
    TreeNode *r1 = new TreeNode(1);
    r1->left = new TreeNode(2);
    r1->right = new TreeNode(3);

    TreeNode *r2 = new TreeNode(1);
    r2->left = new TreeNode(3);
    r2->right = new TreeNode(2);

    Solution s;

    cout << s.leafSimilar(r1, r2);
}