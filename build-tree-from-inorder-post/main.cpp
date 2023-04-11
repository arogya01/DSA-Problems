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
    unordered_map<int, int> mp;
    TreeNode *constructFromPrePost(vector<int> &inorder, vector<int> &post)
    {
        for (auto i : inorder)
        {
            mp[i] = i;
        }
        return build(inorder, post, 0, post.size() - 1);
    }

    TreeNode *build(vector<int> &inorder, vector<int> &post, int in_start, int in_end, int post_start, int post_end)
    {

        if(post_start > post_end || in_start > in_end)
            return nullptr;



        int val = post[post_end];
        int idx = mp[val];

        TreeNode *root = new TreeNode(val);
                            
        int numsLeft = idx - in_start;

        root->left = build(inorder, post, in_start, idx - 1, post_start, post_start + numsLeft - 1);
        root->right = build(inorder, post, idx + 1, in_end, post_start + numsLeft, post_end - 1);

        return root;
    }
};

class Solution2
{
public:
    unordered_map<int, int> val_to_idx;
    TreeNode *constructFromPrePost(vector<int> &pre, vector<int> &post)
    {
        for (int i = 0; i < post.size(); i++)
        {
            val_to_idx[post[i]] = i;
        }

        return build(pre, post, 0, 0, post.size() - 1);
    }

    TreeNode *build(vector<int> &preorder, vector<int> &postorder, int pre_start, int post_start, int post_end)
    {
        if (post_start > post_end)
            return nullptr;
        if (post_start == post_end)
            return new TreeNode(preorder[pre_start]);

        int val = preorder[pre_start];
        int left_child = preorder[pre_start + 1];
        int left_child_idx = val_to_idx[left_child];
        int left_size = left_child_idx - post_start + 1;

        TreeNode *root = new TreeNode(val);
        root->left = build(preorder, postorder, pre_start + 1, post_start, left_child_idx);
        root->right = build(preorder, postorder, pre_start + left_size + 1, left_child_idx + 1, post_end - 1);
        return root;
    }
};

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    Solution2 s;
    vector<int> preorder{1, 2, 4, 5, 3, 6, 7}, postorder{4, 5, 2, 6, 7, 3, 1};
    s.constructFromPrePost(preorder, postorder);
}