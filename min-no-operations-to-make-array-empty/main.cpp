#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums)
    {

        unordered_map<int, int> freqCounter;

        for (int i = 0; i < nums.size(); i++)
        {

            if (freqCounter.find(nums[i]) != freqCounter.end())
            {
                freqCounter[nums[i]]++;
            }
            else
                freqCounter[nums[i]] = 1;
        }

        int finalAns = 0;

        for (auto i : freqCounter)
        {

            if (i.second % 2 != 0 || i.second % 3 != 0)
            {
                return -1;
            }

            if (i.second % 2 == 0)
            {
                finalAns += i.second / 2;
            }

            if (i.second % 3 == 0)
            {
                finalAns += i.second / 3;
            }
        }

        return finalAns;
    }
};

int main()
{
    vector<int> ans{2, 3, 3, 2, 2, 4, 2, 3, 4};

    Solution s;
    cout << s.minOperations(ans);
}