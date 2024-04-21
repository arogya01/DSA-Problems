#include <iostream>
#include <queue>
using namespace std;

class Solution
{
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &r, vector<vector<int>> &b)
    {
        vector<pair<int, int>> adj[n];
        vector<vector<int>> vis(n, vector<int>(2, 0));
        for (int i = 0; i < r.size(); i++)
        {
            int u = r[i][0];
            int v = r[i][1];
            int wt = 0;
            adj[u].push_back({v, wt});
        }
        for (int i = 0; i < b.size(); i++)
        {
            int u = b[i][0];
            int v = b[i][1];
            int wt = 1;
            adj[u].push_back({v, wt});
        }
        vector<int> dist(n, 1e9);
        dist[0] = 0;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for (auto it : adj[0])
        {
            int node = it.first;
            int colour = it.second;
            dist[node] = 1;
            vis[node][colour] = 1;
            pq.push({1, node, colour});
        }
        while (!pq.empty())
        {
            auto it = pq.top();
            int d = it[0];
            int n = it[1];
            int c = it[2];
            pq.pop();
            for (auto it : adj[n])
            {
                int co = it.second;
                int node = it.first;
                if (co != c && !vis[node][co])
                {
                    vis[node][co] = 1;
                    if ((d + 1) < dist[node])
                    {
                        dist[node] = 1 + d;
                        pq.push({dist[node], node, co});
                    }
                    else
                    {
                        pq.push({1 + d, node, co});
                    }
                }
            }
        }
        dist[0] = 0;
        for (int i = 0; i < n; i++)
        {
            if (dist[i] == 1e9)
                dist[i] = -1;
        }
        return dist;
    }
};

int main()
{
    int n = 3,

        vector<vector<int>> redEdges = [ [ 0, 1 ], [ 1, 2 ] ] vector<vector<int>> blueEdges = {};
}