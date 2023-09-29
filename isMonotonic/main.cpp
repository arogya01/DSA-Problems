#include <iostream>

using namespace std;

// leetcode link : https://leetcode.com/problems/monotonic-array/
//  a super inefficient solution from my side.
class Solution
{
public:
    bool isMonotonic(vector<int> &nums)
    {
        // alright, so if it is increase then => increase
        // else , if decreasing => then decrease..

        int monotoneType;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i] == nums[i + 1])
            {
                monotoneType = 0;
                continue;
            }
            else if (nums[i] < nums[i + 1])
            {
                monotoneType = 1;
                break;
            }
            else if (nums[i] > nums[i + 1])
            {
                monotoneType = -1;
                break;
            }
        }

        if (monotoneType == 0)
            return true;

        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (monotoneType == -1 && nums[i] < nums[i + 1])
            {
                return false;
            }
            else if (monotoneType == 1 && nums[i] > nums[i + 1])
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
}