#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numSubseq(vector<int> &nums, int target)
    {
        long long result = 0;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            int minEl = nums[i];
            int maxEl = nums[i];
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[j] > maxEl)
                {
                    maxEl = nums[j];
                }
                if (minEl + maxEl <= target)
                    result += j - i;
            }
        }

        return result % (1000000007);
    }
};

int main()
{
    vector<int> test{3, 5, 6, 7};
    int num = 9;
    cout << Solution().numSubseq(test, num) << endl;
}
