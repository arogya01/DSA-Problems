#include <iostream>

using namespace std;

class Solution
{
public:
    int climbStairs(int n)
    {
        int a = 1, b = 1;
        while (--n)
        {
            cout << a << " " << b << endl;
            a = (b += a) - a;
            cout << a << " " << b << endl;
            cout << endl;
        }
        return b; // change this from a to b
    }
};

int main()
{

    Solution s1;

    int n = 5;
    int res = s1.climbStairs(n);
    cout << "the total possible ways are: " << res << endl;
}