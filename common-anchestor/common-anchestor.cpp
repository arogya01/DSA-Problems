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

    TreeNode(int value, TreeNode *leftNode, TreeNode *rightNode)
    {
        val = value;
        left = leftNode;
        right = rightNode;
    }

    TreeNode *dfsTraverse(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == p || root == q || root == NULL)
            return root;
        TreeNode *parent1 = dfsTraverse(root->left, p, q);
        TreeNode *parent2 = dfsTraverse(root->right, p, q);
        if (parent1 && parent2)
            return root;
        else
            return parent1 ? parent1 : parent2;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {

        return dfsTraverse(root, p, q);
    }
};

int main()
{
    TreeNode *root = new TreeNode(3);
    TreeNode *l1 = new TreeNode(5);
    TreeNode *r1 = new TreeNode(1);
    TreeNode *l2 = new TreeNode(6);
    TreeNode *r2 = new TreeNode(2);
    TreeNode *l3 = new TreeNode(0);
    TreeNode *r3 = new TreeNode(8);
    TreeNode *l4 = new TreeNode(7);
    TreeNode *r4 = new TreeNode(4);

    root->left = l1;
    root->right = r1;
    l1->left = l2;
    l1->right = r2;
    r1->left = l3;
    r1->right = r3;
    r2->left = l4;
    r2->right = r4;

    cout << "running fine." << endl;

    TreeNode *temp = root->dfsTraverse(root, l4, r4);

    cout << temp->val << endl;
}