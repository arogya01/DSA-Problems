#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        intervals.push_back({newInterval});
        sort(intervals.begin(), intervals.end());
        int j = 0, n = intervals.size();
        for (int i = 1; i < n; i++)
        {
            if (intervals[j][1] >= intervals[i][0])
            {
                intervals[j][1] = max(intervals[j][1], intervals[i][1]);
            }
            else
            {
                j++;
                intervals[j] = intervals[i];
            }
        }
        vector<vector<int>> ans;
        for (int i = 0; i <= j; i++)
        {
            ans.push_back(intervals[i]);
        }
        return ans;
    }
};

int main()
{
    vector<vector<int>> vec{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    Solution s1;
    vector<int> newInterval{4, 8};
    s1.insert(vec, newInterval);
}