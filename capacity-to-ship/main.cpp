#include <bits/stdc++.h>
using namespace std;

// question link : https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/description/

class Solution
{
public:
    int shipWithinDays(vector<int> &weights, int days)
    {
        double sum = std::accumulate(weights.begin(), weights.end(), 0);
        int target = std::ceil(sum / days);
        int lo = weights[0];
        int hi = target;
        int i = 1;
        cout << "hi is" << hi;
        while (lo < hi)
        {
            if (lo < hi)
            {
                lo += weights[i];
                i++;
            }
        }

        return lo;
    }
};

int main()
{
    vector<int> arr{3, 2, 2, 4, 1, 4};
    Solution s;
    cout << s.shipWithinDays(arr, 3);
}