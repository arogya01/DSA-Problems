#include <bits/stdc++.h>

using namespace std;

// my iteration with the solution is seemingly not working...

class Solution
{
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {

        vector<int> overlapping;
        for (int i = 0; i <= intervals.size() - 1; i++)
        {
            int count = 0;
            for (int j = 0; j < intervals.size(); j++)
            {
                if (j == i)
                    continue;
                if ((intervals[i][0] >= intervals[j][0] && intervals[i][0] < intervals[j][1]) || (intervals[i][1] > intervals[j][0] && intervals[i][1] <= intervals[j][1]))
                {
                    count++;
                }
            }
            overlapping.push_back(count);
        }

        int min = overlapping[0];
        for (auto i : overlapping)
        {
            cout << "the i's are: " << i << endl;
            if (i < min)
            {
                min = i;
            }
        }

        return min;
    }
};

int main()
{
    Solution s1;

    vector<vector<int>> arr{{1, 100}, {11, 22}, {1, 11}, {2, 12}};

    int count = s1.eraseOverlapIntervals(arr);
    cout << count;
}