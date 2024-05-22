
#include <iostream>
#include <vector>

using namespace std;

// this was my method -> is throwing address sanitizer sorts of errors.
class Solution
{
public:
    int getMaximumGold(vector<vector<int>> &grid)
    {
        int n = grid.size() - 1;
        int m = grid[0].size() - 1;

        int maxSum = -1;

        for (int i = 0; i < grid.size(); i++)
        {
            int sum = -1;
            for (int j = 0; j < grid[i].size(); j++)
            {
                vector<vector<int>> visited(n + 1, vector<int>(m + 1, 0));
                if (grid[i][j] != 0)
                {
                    visited[i][j] = 1;
                    sum = grid[i][j] + rec(i, j, m, n, grid, visited);
                }
            }
            maxSum = max(maxSum, sum);
        }

        return maxSum;
    }

    int rec(int i, int j, int &m, int &n, vector<vector<int>> &grid, vector<vector<int>> &visited)
    {

        int currSum = 0;

        vector<int> dx = {-1, 0, 1, -1};
        vector<int> dy = {0, 1, 0, -1};
        int maxI = -1;
        int maxJ = -1;
        for (int x = 0; x < 4; x++)
        {
            int delx = dx[x] + i;
            int dely = dy[x] + j;
            if (delx >= 0 && delx <= n && dely >= 0 && dely <= m && grid[delx][dely] != 0 && !visited[delx][dely])
            {
                if (grid[delx][dely] >= currSum)
                {
                    maxI = delx;
                    maxJ = dely;
                    currSum = grid[delx][dely];
                    visited[delx][dely] = 1;
                }
            }
        }

        return currSum + rec(maxI, maxJ, m, n, grid, visited);
    }
};

class Solution2
{
};

int main()
{
    vector<vector<int>> grid = {{0, 6, 0}, {5, 8, 7}, {0, 9, 0}};

    Solution s;
    s.getMaximumGold(grid);
}