#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    void computeUnique(vector<vector<int>> &result, vector<int> curr, vector<int> nums, int curr_idx)
    {
        curr.push_back(nums[curr_idx]);
        nums.erase(nums.begin() + curr_idx);
        if (nums.empty())
        {
            result.push_back(curr);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {

            if (i != nums.size() - 1 && nums[i] == nums[i + 1])
            {
                continue;
            }
            computeUnique(result, curr, nums, i);
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        vector<vector<int>> res;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            vector<int> curr;
            if (i != nums.size() - 1 && nums[i] == nums[i + 1])
            {
                continue;
            }

            computeUnique(res, curr, nums, i);
        }

        return res;
    }
};

int main()
{
    Solution s1;
    vector<vector<int>> res;
    vector<int> nums{1, 2, 3};
    res = s1.permuteUnique(nums);

    for (auto i : res)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}