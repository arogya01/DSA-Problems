#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        auto p = [&](int i)
        {
            return (i == 0 || nums[i - 1] < nums[i]);
        };
        int l = -1, r = nums.size();
        while (r - l > 1)
        {
            int mid = l + (r - l) / 2;
            p(mid) ? (l = mid) : (r = mid);
        }
        return l;
    }
};

class MySolution
{
public:
    int findPeakElement(vector<int> &nums)
    {

        if (nums.size() == 1)
            return 0;
        if (nums[0] > nums[1])
            return 0;
        if (nums[nums.size() - 1] > nums[nums.size() - 2])
            return nums.size() - 1;

        int lo = 1;
        int hi = nums.size() - 2;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
                return mid;
            else if (nums[mid] < nums[mid - 1])
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        return -1;
    }
};
int main()
{
    vector<int> sample{1, 1, 1, 3, 4, 5, 6, 4};
    Solution s;
    MySolution s0;
    cout << s.findPeakElement(sample);
    cout << s0.findPeakElement(sample);
}