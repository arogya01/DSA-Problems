#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
private:
    bool detect(int src, vector<vector<int>> &adjList, int vis[])
    {
        vis[src] = 1;
        queue<pair<int, int>> qp;

        qp.push({src, -1});

        while (!qp.empty())
        {
            int node = qp.front().first;
            int parent = qp.front().second;

            qp.pop();

            for (auto adjNode : adjList[node])
            {
                if (!vis[adjNode])
                {
                    vis[adjNode] = 1;
                    qp.push({adjNode, node});
                }
                else if (parent != adjNode)
                {
                    return true;
                }
            }
        }

        return false;
    }

public:
    bool detectCycle(vector<vector<int>> &adjList, int V)
    {
        int vis[V];

        for (int i = 1; i < V; i++)
        {
            if (!vis[i])
            {
                if (detect(i, adjList, vis))
                {
                    return true;
                }
            }
        }

        return false;
    }
};

int main()
{
}