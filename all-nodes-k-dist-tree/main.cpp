#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    unordered_map<TreeNode *, TreeNode *> mp;
    void dfs(TreeNode *root, TreeNode *parent)
    {
        if (!root)
            return;
        if (!parent)
            parent = root;
        else
            mp[root] = parent;
        dfs(root->left, root);
        dfs(root->right, root);
    }

    vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
    {
        queue<TreeNode *> q;
        set<TreeNode *> st;
        dfs(root, NULL);
        q.push(target);
        int cnt = 0;
        vector<int> res;
        while (!q.empty())
        {
            int sz = q.size();
            if (cnt > k)
                break;
            while (sz--)
            {
                auto node = q.front();
                q.pop();
                if (node->left != NULL and !st.count(node->left))
                {
                    q.push(node->left);
                    st.insert(node->left);
                }
                if (node->right != NULL and !st.count(node->right))
                {
                    q.push(node->right);
                    st.insert(node->right);
                }
                if (mp.count(node) and !st.count(mp[node]))
                {
                    q.push(mp[node]);
                    st.insert(mp[node]);
                }
                st.insert(node);
                if (cnt == k)
                {
                    res.push_back(node->val);
                }
            }
            cnt++;
        }
        return res;
    }
};

int main()
{
    // sample test case 1
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    Solution obj;
    vector<int> res = obj.distanceK(root, root->left, 2);
    for (auto x : res)
        cout << x << " ";
    cout << endl;
    return 0;
}