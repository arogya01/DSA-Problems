#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isPerfectSquare(int num)
    {
        // find a number that can perfectly divide the given num,
        //  what should the lower and upper bound be:
        //  lo = 0, hi = num
        // apparently, linear search is faster than binary search in this case..

        int lo = 0;
        int hi = num;

        while (lo <= hi)
        {
            int mid = lo + hi / 2;

            if (mid * mid == num)
                return true;
            if (mid * mid > num)
            {
                hi = mid - 1;
            }
            else
                lo = mid + 1;
        }

        return false;
    }
};

int main()
{

    Solution s;
    std::cout << s.isPerfectSquare(16) << std::endl;
    std::cout << s.isPerfectSquare(25) << std::endl;
    std::cout << s.isPerfectSquare(14) << std::endl;
}