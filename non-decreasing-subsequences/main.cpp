#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> findSubsequences(vector<int> &nums)
    {

        vector<vector<int>> res;
        vector<int> curr;
        if (nums.size() < 2)
            return res;

        for (int i = 0; i < nums.size() - 1; i++)
        {
            curr.push_back(nums[i]);
            compute(nums, curr, res, i + 1);
            curr.pop_back();
        }

        return res;
    }

    void compute(vector<int> &nums, vector<int> curr, vector<vector<int>> &res, int index)
    {

        if (index == nums.size() && curr.size() >= 2)
        {
            res.push_back(curr);
            return;
        }

        if (nums[index] < curr.back())
            return;

        curr.push_back(nums[index]);
        compute(nums, curr, res, index + 1);
        curr.pop_back();
        compute(nums, curr, res, index + 1);
    }
};

int main()
{
    Solution s1;
    vector<int> nums{1, 2, 3};
    s1.findSubsequences(nums);
}