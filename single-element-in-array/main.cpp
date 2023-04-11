#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int lo = 0;
        int hi = nums.size();

        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            int cnt = 1;
            int leftSize = mid;
            int rightSize = nums.size() - mid;
            if (nums[mid - 1] == nums[mid])
            {
                leftSize = leftSize - 1;
                cnt = 2;
            }
            else if (nums[mid + 1] == nums[mid])
            {
                int rightSize = rightSize - 1;
                cnt = 2;
            }

            if (cnt == 1)
                return nums[mid];

            if (leftSize % 2 == 0)
            {
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }

        return -1;
    }
};

int main()
{
    vector<int> vec{1, 1, 2, 3, 3, 4, 4, 8, 8};
    Solution s;
    cout << s.singleNonDuplicate(vec);
}