#include <bits/stdc++.h>

using namespace std;

// Question Link : https://leetcode.com/problems/numbers-with-same-consecutive-differences/

class Solution
{
public:
    vector<int> ans;

    void Solve(int len, int const &k, int num, int digit)
    {
        // Base Case
        if (len == 0)
        {
            ans.push_back(num);
            return;
        }

        // Next Possible digits will have range from 0 - 9
        for (int i = 0; i < 10; i++)
        {
            // Checking for given condition
            if (abs(i - digit) == k)
                Solve(len - 1, k, num * 10 + i, i);
        }
    }

    vector<int> numsSameConsecDiff(int n, int k)
    {

        for (int i = 1; i <= 9; i++)
        {
            Solve(n - 1, k, i, i);
        }

        return ans;
    }
};

int main()
{
    int n = 3, k = 7;

    Solution *s1 = new Solution();

    vector<int> res = s1->numsSameConsecDiff(n, k);

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
}