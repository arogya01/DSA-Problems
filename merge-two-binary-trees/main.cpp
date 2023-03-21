#include <bits/stdc++.h>

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

class Solution
{
public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
    {
        if (!t1)
            return t2;
        if (!t2)
            return t1;
        queue<TreeNode *> q1, q2;
        q1.push(t1);
        q2.push(t2);
        while (!q1.empty() && !q2.empty())
        {
            TreeNode *n1 = q1.front();
            TreeNode *n2 = q2.front();
            q1.pop();
            q2.pop();
            n1->val += n2->val;
            if (n1->left && n2->left)
            {
                q1.push(n1->left);
                q2.push(n2->left);
            }
            else if (n2->left)
            {
                n1->left = n2->left;
            }
            if (n1->right && n2->right)
            {
                q1.push(n1->right);
                q2.push(n2->right);
            }
            else if (n2->right)
            {
                n1->right = n2->right;
            }
        }
        return t1;
    }
};

int main()
{
    TreeNode *r1 = new TreeNode(1);
    r1->left = new TreeNode(3);
    r1->right = new TreeNode(2);

    TreeNode *r2 = new TreeNode(2);
    r2->left = new TreeNode(5);

    Solution s;
    s.mergeTrees(r1, r2);

    cout << "hey codespaces" << endl;
}