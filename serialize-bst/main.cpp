#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

int main()
{
    // TreeNode *root = new TreeNode(5);
    // TreeNode *leftNode = new TreeNode(2);
    // TreeNode *rightNode = new TreeNode(7);
    // root->left = leftNode;
    // root->right = rightNode;
    // leftNode->right = new TreeNode(4);
    // rightNode->left = new TreeNode(6);

    // Codec *ser = new Codec();
    // string tree = ser->serialize(root);
    // cout << "tree is : " << tree << endl;

    Codec *deser = new Codec();
    string preorder_str = "5,3,2,4,7,6,8";
    TreeNode *root = deser->deserialize(preorder_str);
    // Test the deserialized tree
    cout << root->val << endl;               // output: 5
    cout << root->left->val << endl;         // output: 3
    cout << root->left->left->val << endl;   // output: 2
    cout << root->left->right->val << endl;  // output: 4
    cout << root->right->val << endl;        // output: 7
    cout << root->right->left->val << endl;  // output: 6
    cout << root->right->right->val << endl; // output: 8
}