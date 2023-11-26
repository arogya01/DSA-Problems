#include <iostream>

using namespace std;

// will push the solution some other time....
class Solution
{
public:
    vector<int> getSumAbsoluteDifferences(vector<int> &nums)
    {
        vector<int> res;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
        }

        int size = nums.size() - 1;
        for (int i = 0; i < nums.size(); i++)
        {
            int el = abs(sum - nums[i]);
            el = abs(el - (nums[i] * size));
            res.push_back(el);
        }

        return res;
    }
};

int main()
{
}