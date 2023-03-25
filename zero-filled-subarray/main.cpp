#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    long long zeroFilledSubarray(vector<int> &nums)
    {
        int cnt = 0;
        long long res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
            {
                cnt++;
            }
            else
            {
                if (cnt == 1)
                    res += 1;
                if (cnt > 1)
                {
                    res += cnt * (cnt - 1);
                }
                cnt = 0;
            }
        }

        return res;
    }
};

int main()
{
    vector<int> nums{1, 3, 0, 0, 2, 0, 0, 4};
    Solution s;
    cout << s.zeroFilledSubarray(nums) << endl;
}