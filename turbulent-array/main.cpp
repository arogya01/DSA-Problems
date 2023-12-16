#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxTurbulenceSize(vector<int> &A)
    {
        int N = A.size();
        int ans = 1;
        int anchor = 0;

        for (int i = 1; i < N; ++i)
        {
            int c = compare(A[i - 1], A[i]);
            if (c == 0)
            {
                anchor = i;
            }
            else if (i == N - 1 || c * compare(A[i], A[i + 1]) != -1)
            {
                ans = std::max(ans, i - anchor + 1);
                anchor = i;
            }
        }

        return ans;
    }

private:
    int compare(int a, int b)
    {
        if (a == b)
            return 0;
        return a > b ? 1 : -1;
    }
};
int main()
{

    vector<int> arr{9, 4, 2, 10, 7, 8, 8, 1, 9};
    Solution s;
    s.maxTurbulenceSize(arr);
}