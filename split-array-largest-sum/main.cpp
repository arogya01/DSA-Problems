#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {
        int totalSum = 0;
        int res = 0;
        int largestMinSum = 0;
        int initialSum = 0;
        int y = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            totalSum += nums[i];
        }

        for (int i = 0; i < k; i++)
        {
            initialSum += nums[i];
        }
        largestMinSum = max(initialSum, totalSum - initialSum);
        res = largestMinSum;
        int precedingTotal = 0;
        for (int i = k; i < nums.size(); i++, y++)
        {
            initialSum = initialSum + nums[i] - nums[y];
            precedingTotal += nums[y];

            largestMinSum = max_element({initialSum, totalSum - initialSum, totalSum - initialSum - precedingTotal});
            largestMinSum = max(largestMinSum, precedingTotal);
            res = min(largestMinSum, res);
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums{7, 2, 5, 10, 8};
    cout << s.splitArray(nums, 2);
}