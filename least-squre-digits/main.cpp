#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool hasIntegerSquareRoot(int num)
    {
        if (num == 0 || num == 1)
        { // Special cases
            return true;
        }

        for (int i = 1; i * i <= num; ++i)
        {
            if (num == i * i)
            {
                cout << "treu" << endl;
                return true;
            }
        }

        cout << "false" << endl;
        return false;
    }

    int numSquares(int n)
    {
        int finalCount = 0;
        int remSum = n;
        for (int i = n; i > 0; i--)
        {
            if (n == 0)
            {
                break;
            }
            if (hasIntegerSquareRoot(i))
            {
                finalCount++;
                n = n - i;
            }
        }

        return finalCount;
    }
};

int main()
{
    Solution s;
    s.numSquares(2);
}