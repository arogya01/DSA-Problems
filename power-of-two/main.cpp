#include <iostream>

using namespace std;

class Solution
{
public:
    bool isPowerOfTwo(int n)
    {
        if (n < 0)
            return false;
        int x = 1;
        while (x <= n)
        {
            x *= 2;
        }

        return x == n;
    }
};

int main()
{
    Solution s;
    s.isPowerOfTwo(16);
}