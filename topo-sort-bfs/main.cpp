#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> topoSort(int V, vector<int> adj[])
    {
        vector<int> inDegree(V, 0);

        for (int i = 0; i < V; i++)
        {
            for (auto it : adj[V])
            {
                inDegree[it]++;
            }
        }
        queue<int> qp;

        for (int i = 0; i < V; i++)
        {
            if (inDegree[i] == 0)
            {
                qp.push(i);
            }
        }

        vector<int> topoSort;

        while (!qp.empty())
        {

            int node = qp.front();
            qp.pop();
            topoSort.push_back(node);

            for (auto it : adj[node])
            {
                inDegree[it]--;
                if (inDegree[it] == 0)
                    qp.push(it);
            }
        }

        return topoSort;
    }
};

int main()
{
}