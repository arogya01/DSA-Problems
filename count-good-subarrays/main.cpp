#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    long long countGood(vector<int> &nums, int k)
    {
        int i = 0, j = 0, n = nums.size();
        unordered_map<int, int> mp;
        long long int c = 0, ans = 0;
        while (j < n)
        {
            mp[nums[j]]++;
            c += mp[nums[j]] - 1;
            while (i < j and c >= k)
            {
                ans += n - j;
                mp[nums[i]]--;
                c -= mp[nums[i]];
                i++;
            }
            j++;
        }
        return ans;
    }
};

int main()
{
    vector<int> nums{3, 1, 4, 3, 2, 2, 4};
    int k = 2;

    Solution s;
    int l = s.countGood(nums, k);
    cout << l << endl;
}