#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums, int target)
    {

        int count = 0;                // Initialize the count of subarrays
        int sum = 0;                  // Initialize the current sum of subarray
        unordered_map<int, int> freq; // A map to store the frequency of each sum value
        for (int i = 0; i < nums.size(); i++)
        {                   // Loop through the range
            sum += nums[i]; // Update the current sum
            if (sum == target)
                count++; // If the current sum is equal to target, increment count
            if (freq.find(sum - target) != freq.end())
                count += freq[sum - target]; // If there is a previous subarray with sum equal to current sum - target, add its frequency to count
            freq[sum]++;                     // Increment the frequency of current sum
        }
        return count; // Return the count of subarrays
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 1, 1};
    int k = 2;
    cout << s.subarraySum(nums, k) << endl;
    return 0;
}
