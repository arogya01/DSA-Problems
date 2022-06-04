#include <bits/stdc++.h>
using std::cout, std::endl, std::vector;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {

        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int tempSum = 0;
            vector<int> tempArr;
            int k = i;
            int j = i;
            while (j <= k && k < nums.size())
            {

                tempSum += nums[j];
                if (k == nums.size() - 1)
                {
                    break;
                }

                if (j == k)
                {
                    j = i;
                    k++;
                    tempArr.push_back(tempSum);
                    tempSum = 0;
                }
                else
                {
                    j++;
                }
            }

            if (!tempArr.empty())
            {

                int max = *max_element(tempArr.begin(), tempArr.end());
                if (max > sum)
                {
                    sum = max;
                }
            }
        }

        return sum;
    }
};

int main()
{
    vector<int> nums{5, 4, -1, 7, 8};
    Solution s1;

    int res = s1.maxSubArray(nums);

    cout << res;
}