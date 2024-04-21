#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> findFarmland(vector<vector<int>> &graph)
    {
        vector<vector<int>> ans;
        int m = graph.size();
        int n = graph[m].size();
        vector<vector<int>> vis(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (graph[i][j] == 1 && !vis[i][j])
                {
                    bfs(i, j, ans, graph, vis);
                }
            }
        }

        return ans;
    }

    void bfs(int i, int j, vector<vector<int>> &ans, vector<vector<int>> &graph,
             vector<vector<int>> &vis)
    {

        queue<pair<int, int>> qp;
        vector<int> subAns;
        qp.push({i, j});
        int m = graph.size();
        int n = graph[m].size();
        subAns.push_back(i);
        subAns.push_back(j);
        vector<int> dx{1, -1, 0, 0};
        vector<int> dy{0, 0, 1, -1};

        while (!qp.empty())
        {

            std::pair<int, int> front = qp.front();
            qp.pop();
            int row = front.first;
            int col = front.second;

            vis[row][col] = 1;
            if (row >= 0 && col >= 0 && row + 1 < m && col + 1 < n && graph[row + 1][col] == 1 && graph[row][col + 1] == 1)
            {
                qp.push({row + 1, col + 1});
                vis[row][col + 1] = 1;
                vis[row + 1][col] = 1;
                subAns.push_back(row + 1);
                subAns.push_back(col + 1);
            }
        }

        for (auto i : subAns)
        {
            cout << i << endl;
        }
        int siz = subAns.size() - 1;
        // ans.push_back({subAns[0],subAns[1],subAns[siz-1],subAns[siz]});
    }
};

int main()
{

    vector<vector<int>> land = {{1, 0, 0}, {0, 1, 1}, {0, 1, 1}};

    Solution s;
    s.findFarmland(land);
}