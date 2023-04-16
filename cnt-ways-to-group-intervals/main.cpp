#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution
{
public:
    int countWays(vector<vector<int>> &a)
    {
        sort(a.begin(), a.end());
        int cnt = 0;
        int j = 0;
        for (int i = 1; i < a.size(); i++)
        {
            if (a[j][1] >= a[i][0])
            {
                a[j][1] = max(a[j][1], a[i][1]);
                cnt++;
            }
            else
            {
                j = i;
            }
        }

        cout << "overlap count is:" << cnt << endl;

        return pow(2, a.size() - cnt);
    }
};

int main()
{
    vector<vector<int>> vec{{5, 11}, {20, 22}, {1, 3}, {21, 22}, {11, 11}};
    Solution s;
    s.countWays(vec);
}
