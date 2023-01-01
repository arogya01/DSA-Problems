#include <bits/stdc++.h>

using namespace std;

// lc link: https://leetcode.com/problems/count-nodes-with-the-highest-score/description/

class Solution
{
public:
    long long dfs(int node, vector<vector<int>> &adj, long long &ans, long long &cnt, int &n)
    {
        long long l = 0, r = 0;
        if (adj[node].size() >= 1)
        {
            l = dfs(adj[node][0], adj, ans, cnt, n);
        }
        if (adj[node].size() >= 2)
        {
            r = dfs(adj[node][0], adj, ans, cnt, n);
        }
        long long rest = n - 1 - r - l;
        long long score = (l == 0 ? 1 : l) * (r == 0 ? 1 : r) * (rest == 0 ? 1 : rest);
        if (score == ans)
        {
            ++cnt;
        }
        else if (score > ans)
        {
            ans = score;
            cnt = 1;
        }
        return l + r + 1;
    }
    int countHighestScoreNodes(vector<int> &parents)
    {
        long long ans = 0;
        long long cnt = 0;
        vector<vector<int>> adj;
        int n;
        n = parents.size();
        adj.resize(n);
        for (int i = 1; i < parents.size(); i++)
        {
            adj[parents[i]].push_back(i);
        }
        dfs(0, adj, ans, cnt, n);
        return cnt;
    }
};

int main()
{
    vector<int> arr{-1, 2, 0, 2, 0};
    Solution s1;
    int res = s1.countHighestScoreNodes(arr);
    cout << res;
}