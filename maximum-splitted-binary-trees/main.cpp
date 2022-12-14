#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

static int MOD = 1e9 + 7;

class Solution
{
public:
    long long totalTreeSum = 0, result = 0;
    void getTotalTreeSum(TreeNode *root) // Get total sum of the tree.
    {
        if (!root)
            return;
        totalTreeSum += root->val;
        getTotalTreeSum(root->left);
        getTotalTreeSum(root->right);
    }

    int SumUnder(TreeNode *root) // Get the totalSum under the node `root` including root.
    {
        if (!root)
            return 0;
        int sumUnderLeft = SumUnder(root->left), sumUnderRight = SumUnder(root->right);
        // Get the sum of left and right subtree under node 'root'
        cout << max({result, (totalTreeSum - sumUnderLeft) * sumUnderLeft, (totalTreeSum - sumUnderRight) * sumUnderRight}) << endl;
        result = max({result, (totalTreeSum - sumUnderLeft) * sumUnderLeft, (totalTreeSum - sumUnderRight) * sumUnderRight});
        // Get the max product after making left or right subtrees as seprarate tree.
        return sumUnderLeft + sumUnderRight + root->val;
    }

    int maxProduct(TreeNode *root)
    {
        getTotalTreeSum(root);
        cout << totalTreeSum << endl;
        SumUnder(root);
        return result % MOD;
    }
};

int main()
{
    TreeNode *root = new TreeNode(1);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(3);
    root->left = left;
    root->right = right;
    left->left = new TreeNode(4);
    left->right = new TreeNode(5);
    right->left = new TreeNode(6);

    Solution s1;
    int maxVal = s1.maxProduct(root);
    cout << maxVal << endl;
    cout << "whatever" << endl;
}