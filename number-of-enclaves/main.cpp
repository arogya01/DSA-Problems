#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<bool>> visited;
    vector<int> adderx = {0, 0, 1, -1};
    vector<int> addery = {1, -1, 0, 0};

    int explore_area(vector<vector<int>> &grid, int i, int j)
    {
        int totalarea = 1;
        for (int k = 0; k < 4; k++)
        {
            if ((i + addery[k]) < grid.size() && (i + addery[k]) >= 0 && (j + adderx[k]) < grid[0].size() && (j + adderx[k]) >= 0 && grid[i + addery[k]][j + adderx[k]] == 1 && !visited[i + addery[k]][j + adderx[k]])
            {
                visited[i + addery[k]][j + adderx[k]] = true;
                totalarea += explore_area(grid, i + addery[k], j + adderx[k]);
            }
        }
        return totalarea;
    }

    
    int numEnclaves(vector<vector<int>> &grid)
    {
        // Using DFS
        visited.assign(grid.size(), vector<bool>(grid[0].size(), false));
        int total_islands = 0, boundary_islands = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1 && !visited[i][j])
                {
                    visited[i][j] = true;
                    total_islands += explore_area(grid, i, j);
                }
            }
        }
        visited.assign(grid.size(), vector<bool>(grid[0].size(), false));
        for (int i = 0; i < grid.size(); i++)
        {
            if (grid[i][0] == 1 && !visited[i][0])
            {
                visited[i][0] = true;
                boundary_islands += explore_area(grid, i, 0);
            }
            if (grid[i][grid[0].size() - 1] == 1 && !visited[i][grid[0].size() - 1])
            {
                visited[i][grid[0].size() - 1] = true;
                boundary_islands += explore_area(grid, i, grid[0].size() - 1);
            }
        }
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[0][j] == 1 && !visited[0][j])
            {
                visited[0][j] = true;
                boundary_islands += explore_area(grid, 0, j);
            }
            if (grid[grid.size() - 1][j] == 1 && !visited[grid.size() - 1][j])
            {
                visited[grid.size() - 1][j] = true;
                boundary_islands += explore_area(grid, grid.size() - 1, j);
            }
        }
        return (total_islands - boundary_islands);
    }
};

int main()
{

    vector<vector<int>> sample{{0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};

    Solution s;

    cout << s.numEnclaves(sample) << endl;
}