#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &A, int k)
    {
        if (k == 0)
            return 0;
        long i = 0, j = 0, N = A.size(), prod = 1, ans = 0;
        for (; j < N; ++j)
        {
            prod *= A[j];
            while (i <= j && prod >= k)
                prod /= A[i++];
            ans += j - i + 1;
        }
        return ans;
    }
};

int main()
{
    vector<int> A = {10, 5, 2, 6};
    int k = 100;
    Solution s;
    cout << s.numSubarrayProductLessThanK(A, k);
}