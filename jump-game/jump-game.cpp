#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

int maxResult(vector<int> &nums, int k)
{

    int res = nums[0];
    int vecSize = nums.size() - 1;
    if (nums.size() == 1)
    {
        return res;
    }

    if (k >= nums.size())
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
            {
                res += nums[i];
            }
        }
    }
    else
    {
        for (int i = 0; i < nums.size(); i = min(vecSize, i + k))
        {
            int highest = INT_MIN;

            for (int j = i + 1; j <= i + k; j++)
            {
                if (nums[j] > highest)
                {
                    highest = nums[j];
                }
            }

            res += highest;
            // i = i+k;
        }
    }

    return res;
}

int main()
{
    vector<int> nums{1, -1, -2, 4, -7, 3};

    int result = maxResult(nums, 2);

    cout << result;
}