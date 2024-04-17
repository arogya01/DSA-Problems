#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    bool dfsCheck(int node, vector<vector<int>> adjList, vector<int> vis, vector<int> pathVis)
    {

        vis[node] = 2;

        // traversing for adj nodes
        for (auto it : adjList[node])
        {
            if (!vis[it])
            {
                if (dfsCheck(it, adjList, vis, pathVis) == true)
                {
                    return true;
                }
            }
            else if (pathVis[it] == 2)
            {
                return true;
            }
        }

        vis[node] = 1;
        return false;
    }

public:
    bool detectCycle(vector<vector<int>> adjList)
    {
        int m = adjList.size();
        vector<int> vis(m, 0);
        vector<int> pathVis(m, 0);

        for (int i = 1; i < m; i++)
        {
            if (!vis[i])
            {
                if (dfsCheck(i, adjList, vis, pathVis) == true)
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
    vector<vector<int>> adjList;

    adjList[1].push_back(2);
    adjList[2].push_back(3);
    adjList[3].push_back(4);
    adjList[3].push_back(7);
    adjList[4].push_back(5);
    adjList[5].push_back(6);
    adjList[7].push_back(5);
    adjList[8].push_back(9);
    adjList[8].push_back(2);
    adjList[9].push_back(10);
    adjList[10].push_back(8);

    Solution s;
    cout << s.detectCycle(adjList);
}