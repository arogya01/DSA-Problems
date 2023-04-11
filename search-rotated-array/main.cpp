#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int pivot = -1;
        int el1 = -1;
        int el2 = -1;

        if (nums.size() == 1)
        {
            if (nums[0] == target)
                return 0;
            else
                return -1;
        }
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (!(nums[i] < nums[i + 1]))
            {
                pivot = i;
                break;
            }
        }

        if (pivot == -1)
        {
            el1 = performbs(nums, target, 0, nums.size() - 1);
        }
        else
        {
            el1 = performbs(nums, target, 0, pivot);
            el2 = performbs(nums, target, pivot + 1, nums.size() - 1);
        }
        if (el1 != -1)
        {
            return el1;
        }
        else if (el2 != -1)
        {
            return el2;
        }

        return -1;
    }

    int performbs(vector<int> nums, int target, int lo, int hi)
    {
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target)
                return mid;

            if (nums[mid] < target)
            {
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }

        return -1;
    }
};

int main()
{
    vector<int> nums = {1, 3};
    int target = 0;

    Solution s;
    cout << s.search(nums, target);
}