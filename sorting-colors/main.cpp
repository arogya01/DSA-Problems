#include <bits/stdc++.h>
using namespace std;

// problem link: https://leetcode.com/problems/sort-colors/description/
class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        // we're using 3-way partioning algo, specifically used to sort through 3-distinct values
        int low = 0;
        int mid = 0;
        int high = nums.size() - 1;

        while (low <= high)
        {
            if (nums[mid] == 0)
            {
                swap(nums[low], nums[mid]);
                low++;
                high++;
            }
            else if (nums[mid] == 1)
            {
                mid++;
            }
            else
            {
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
};

int main()
{
    vector<int> nums{2, 0, 1};
    Solution s1;
    s1.sortColors(nums);
}