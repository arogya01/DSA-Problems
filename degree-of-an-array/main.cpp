#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int findShortestSubArray(vector<int> &nums)
    {
        unordered_map<int, int> freq, left;
        int degree = 0, shortestLength = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            int num = nums[i];
            if (left.find(num) == left.end())
            {
                left[num] = i;
            }
            freq[num]++;
            if (freq[num] == degree)
            {
                shortestLength = min(shortestLength, i - left[num] + 1);
            }
            else if (freq[num] > degree)
            {
                degree = freq[num];
                shortestLength = i - left[num] + 1;
            }
        }

        return shortestLength;
    };
};

int main()
{
    vector<int> vec{1, 2, 2, 1, 2, 1, 1, 1, 1, 2, 2, 2};
    Solution s1;
    cout << s1.findShortestSubArray(vec);
}