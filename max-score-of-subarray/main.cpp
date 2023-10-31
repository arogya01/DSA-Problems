#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution
{
public:
  int maximumScore(vector<int> &nums, int k)
  {
    int ans = solve(nums, k);
    reverse(nums.begin(), nums.end());
    return max(ans, solve(nums, nums.size() - k - 1));
  }

  int solve(vector<int> &nums, int k)
  {
    int n = nums.size();
    vector<int> left(k, 0);
    int currMin = INT_MAX;
    for (int i = k - 1; i >= 0; i--)
    {
      currMin = min(currMin, nums[i]);
      left[i] = currMin;
    }

    vector<int> right;
    currMin = INT_MAX;
    for (int i = k; i < n; i++)
    {
      currMin = min(currMin, nums[i]);
      right.push_back(currMin);
    }

    int ans = 0;
    for (int j = 0; j < right.size(); j++)
    {
      currMin = right[j];
      int i = lower_bound(left.begin(), left.end(), currMin) - left.begin();
      int size = (k + j) - i + 1;
      ans = max(ans, currMin * size);
    }

    return ans;
  }
};

class Solution1
{
public:
  // Function to return the maximum score of a good subarray
  int maximumScore(vector<int> &nums, int k)
  {
    // Initialize the maximum score as nums[k]
    int maxScore = nums[k];
    // Initialize the minimum element in the subarray as nums[k]
    int minElement = nums[k];
    // Initialize the left and right pointers as k
    int left = k;
    int right = k;
    // Loop until we reach the boundaries of the array or find a smaller element
    while (true)
    {
      // If both left and right pointers can move
      if (left > 0 && right < nums.size() - 1)
      {
        // If the left element is larger than the right element
        if (nums[left - 1] > nums[right + 1])
        {
          // Move the left pointer to the left
          left--;
          // Update the minimum element in the subarray
          minElement = min(minElement, nums[left]);
        }
        // Otherwise
        else
        {
          // Move the right pointer to the right
          right++;
          // Update the minimum element in the subarray
          minElement = min(minElement, nums[right]);
        }
      }
      // If only the left pointer can move
      else if (left > 0)
      {
        // Move the left pointer to the left
        left--;
        // Update the minimum element in the subarray
        minElement = min(minElement, nums[left]);
      }
      // If only the right pointer can move
      else if (right < nums.size() - 1)
      {
        // Move the right pointer to the right
        right++;
        // Update the minimum element in the subarray
        minElement = min(minElement, nums[right]);
      }
      // If neither pointer can move
      else
      {
        // Break out of the loop
        break;
      }
      // Update the maximum score by multiplying the minimum element with the length of the subarray
      maxScore = max(maxScore, minElement * (right - left + 1));
    }
    // Return the maximum score
    return maxScore;
  }
};

int main()
{
  vector<int> nums{1, 4, 3, 7, 4, 5};

  Solution s;

  s.maximumScore(nums, 3);
}