#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int alternatingSubarray(vector<int> &nums)
    {

        int sizeOfArray = nums.size();
        int lo = 0;
        int ans = 1;
        int endOfArray = nums.size() - 1;
        for (int i = 1; i < sizeOfArray; i++)
        {
            int diff = nums[i] - nums[i - 1];

            if (i == endOfArray || diff * (nums[i + 1] - nums[i]) != -1)
            {
                ans = std::max(ans, i + lo - 1);
                lo = i;
            }
        }

        return ans;
    }
};

int main()
{
    vector<int> arr{31, 32, 31, 32, 33};
    Solution s;
    s.alternatingSubarray(arr);
}