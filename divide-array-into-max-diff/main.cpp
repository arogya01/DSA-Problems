#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> divideArray(vector<int> &nums, int k)
    {

        if (nums.size() < 3)
            return {};

        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i = i + 2)
        {

            if (abs(nums[i] - nums[i + 1]) <= k && abs(nums[i + 1] - nums[i + 2]) <= k &&
                abs(nums[i] - nums[i - 2]) <= k)
            {
                ans.push_back({i, i + 1, i + 2});
            }
            else
            {
                return {};
            }
        }

        return ans;
    }
};

int main()
{
    vector<int> l1{1, 3, 4, 8, 7, 9, 3, 5, 1};

    Solution s;
    s.divideArray(l1, 2);
}