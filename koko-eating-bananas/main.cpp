#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isValid(vector<int> piles, int mid, int h)
    {
        int cnt = 0;

        for (auto pile : piles)
        {
            if (pile % mid == 0)
            {
                cnt += (pile / mid);
            }
            else
            {
                cnt += (pile / mid);
                cnt++;
            }
        }

        return cnt <= h;
    }

    int minEatingSpeed(vector<int> &piles, int h)
    {
        // return the minimum integer k that she can eat all the bananas within h hours...
        int start = 1;
        int end = *max_element(piles.begin(), piles.end());
        int k = 0;

        while (start <= end)
        {
            int mid = start + (end - start) / 2;

            if (isValid(piles, mid, h))
            {
                k = mid;
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }

        return k;
    }
};

int main()
{
    Solution sol;
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    cout << sol.minEatingSpeed(piles, h) << endl;
    return 0;
}