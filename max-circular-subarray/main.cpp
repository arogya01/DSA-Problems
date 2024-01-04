#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int currMax = nums[0];
        int maxSum = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            int num = nums[i];
            currMax = max(num, currMax + num);
            maxSum = max(maxSum, currMax);
        }

        return maxSum;
    }

    int maxSubarraySumCircular(vector<int> &nums)
    {
    }
};

int main()
{
}