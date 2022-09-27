#include <bits/stdc++.h>

using namespace std;

// Question Link : https://leetcode.com/problems/maximum-length-of-repeated-subarray/
int findLength(vector<int> &nums1, vector<int> &nums2)
{

    int m = nums1.size(), n = nums2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int ans = 0;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (nums1[i - 1] == nums2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                ans = max(ans, dp[i][j]);
            }
        }
    }

    return ans;
}

int main()
{
    vector<int> v1{1, 2, 3, 2, 1};
    vector<int> v2{3, 2, 1, 4, 7};

    int len = findLength(v1, v2);
    cout << len;
}