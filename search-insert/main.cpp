#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int searchInsert(vector<int> &nums, int target)
{
    int low = 0, high = nums.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (nums[mid] < target)
        {
            low = mid + 1;
        }
        else
            high = mid - 1;
    }

    return low;
}

int main()
{
    vector<int> nums{1, 3};
    int target = 2;

    int index = searchInsert(nums, target);
    cout << "index for target is: " << index;
}