#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> sortArray(vector<int> &nums)
    {

        int l = 0;
        int r = nums.size() - 1;
        divide(nums, l, r);
        return nums;
    }

    void divide(vector<int> &nums, int l, int r)
    {
        if (l >= r)
            return;
        int mid = l + ((r - l) / 2);

        divide(nums, l, mid);
        divide(nums, mid + 1, r);
        merge(nums, l, mid, r);
    }

    void merge(vector<int> &nums, int l, int mid, int r)
    {

        int x1 = mid - l + 1;
        int x2 = r - mid;

        vector<int> n1(x1);
        vector<int> n2(x2);

        for (int i = 0; i < x1; i++)
        {
            n1[i] = nums[l + i];
        }

        for (int j = 0; j < x2; j++)
        {
            n2[j] = nums[mid + 1 + j];
        }

        int i = 0, j = 0, k = l;
        while (i < x1 && j < x2)
        {
            if (n1[i] < n2[j])
            {
                nums[k] = n1[i];
                i++;
            }
            else
            {
                nums[k] = n2[j];
                j++;
            }
            k = k + 1;
        }

        while (i < x1)
        {
            nums[k] = n1[i];
            i++;
            k++;
        }
        while (j < x2)
        {
            nums[k] = n2[j];
            j++;
            k++;
        }
    }
};

int main()
{
    Solution s;
    vector<int> nums = {5, 2, 3, 1};
    vector<int> ans = s.sortArray(nums);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}