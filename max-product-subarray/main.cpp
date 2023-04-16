#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int maxEl = nums[0];
        int minEl = nums[0];
        int result = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            int temp = maxEl;
            maxEl = max(max(maxEl * nums[i], minEl * nums[i]), nums[i]);
            minEl = min(min(temp * nums[i], minEl * nums[i]), nums[i]);
            result = max(result, maxEl);
        }

        return result;
    }
};

int main()
{
    vector<int> ex{2, 3, -2, 4};
    Solution s;
    cout << s.maxProduct(ex);
}