#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
private:
    bool isValid(vector<int> &candies, long long k, int max_candies)
    {
        long long child_cnt = 0;

        for (auto candies : candies)
            child_cnt += candies / max_candies;

        return child_cnt >= k;
    }

public:
    int maximumCandies(vector<int> &candies, long long k)
    {
        int start = 1;
        int end = *max_element(candies.begin(), candies.end());
        int res = 0;

        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            if (isValid(candies, k, mid))
            {
                res = mid;
                start = mid + 1;
            }
            else
                end = mid - 1;
        }

        return res;
    }
};

int main()
{
    vector<int> vec{5, 8, 6};
    int k = 3;
    Solution sol;
    cout << sol.maximumCandies(vec, k);
}