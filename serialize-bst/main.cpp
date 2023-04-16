#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string result;
        string res = serializeTree(root);
        cout << "res is : " << res << endl;
        return res;
        // result.find("null");
    }

    TreeNode *deserializeTwo(string data)
    {
        stringstream ss(data);
        string item;

        TreeNode *root = nullptr;
        while (getline(ss, item, '-'))
        {
            root = insert(root, stoi(item));
        }

        return root;
    }

    TreeNode *insert(TreeNode *root, int val)
    {
        if (root == NULL)
        {
            TreeNode *temp = new TreeNode(val);
            return temp;
        }

        if (val <= root->val)
            root->left = insert(root->left, val);

        else
            root->right = insert(root->right, val);

        return root;
    }

    string serializeTree(TreeNode *node)
    {
        if (!node)
            return "null";
        vector<int> la{1, 2, 3};
        string left = serializeTree(node->left);
        string right = serializeTree(node->right);

        string res = to_string(node->val) + "," + left + "," + right;

        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode *buildTree(vector<int> &preorder, int lower_bound, int upper_bound)
    {
        if (preorder.empty() || preorder[0] < lower_bound || preorder[0] > upper_bound)
        {
            return nullptr;
        }
        int root_val = preorder[0];
        preorder.erase(preorder.begin());
        TreeNode *root = new TreeNode(root_val);
        root->left = buildTree(preorder, lower_bound, root_val);
        root->right = buildTree(preorder, root_val, upper_bound);
        return root;
    }

    TreeNode *deserialize(string preorder_str)
    {
        vector<int> preorder;
        size_t start = 0, end = 0;
        while ((end = preorder_str.find(',', start)) != string::npos)
        {
            preorder.push_back(stoi(preorder_str.substr(start, end - start)));
            start = end + 1;
        }
        preorder.push_back(stoi(preorder_str.substr(start)));

        return buildTree(preorder, numeric_limits<int>::min(), numeric_limits<int>::max());
    }
};
int main()
{

    Codec *deser = new Codec();
    string preorder_str = "2-1-3-";
    TreeNode *root = deser->deserializeTwo(preorder_str);
    // Test the deserialized tree
    cout << root->val << endl;        // output: 2
    cout << root->left->val << endl;  // output: 1
    cout << root->right->val << endl; // output: 3

    string test{"45981"};
    sort(test.begin(), test.end());
    cout << test << endl;
}