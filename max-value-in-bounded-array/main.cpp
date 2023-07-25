#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxValue(int n, int index, int maxSum)
    {
        // either the adjacent el can be equal or with diff less than one, oh well...
        // it shouldn't cross max-sum and we also want to increment index...

        int delta = maxSum - n;
        int el = 0;
        int sum = 0;
        while (sum <= maxSum)
        {
            el++;
            sum += (el - 1) * (n - 1);
            sum += 1;
        }

        return el - 1;
    }
};

int main()
{
    Solution s;
    cout << s.maxValue(4, 2, 6);
    cout << s.maxValue(6, 1, 10);
}