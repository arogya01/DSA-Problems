#include <iostream>

using namespace std;

// leetcode link : https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/description/

class Solution
{
public:
    int minimizedMaximum(int n, vector<int> &v)
    {
        int mx = 100009, mn = 1;
        int ans = v[0], k, mid;
        while (mn <= mx)
        {
            mid = (mx - mn) / 2 + mn;
            k = 0;
            for (auto &i : v)
            {
                if (i % mid)
                {
                    k += i / mid + 1;
                }
                else
                {
                    k += i / mid;
                }
            }
            if (k > n)
            {
                mn = mid + 1;
            }
            else
            {
                ans = mid;
                mx = mid - 1;
            }
        }
        return ans;
    }
};

int main()
{
}