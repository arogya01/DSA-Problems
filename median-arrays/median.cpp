#include <iostream>
#include <vector>

using namespace std;

// we can also use binary seach for this question.

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{

    vector<int> res;

    int i = 0, j = 0;

    for (; i < nums1.size() && j < nums2.size();)
    {

        if (nums1[i] < nums2[j])
        {
            res.push_back(nums1[i]);
            i++;
        }
        else
        {
            res.push_back(nums2[j]);
            j++;
        }
    }

    for (; i < nums1.size(); i++)
    {
        res.push_back(nums1[i]);
    }

    for (; j < nums2.size(); j++)
    {
        res.push_back(nums2[j]);
    }

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
    return 2.2;
}

int main()
{
    vector<int> nums1{1, 3, 5, 6, 8, 9, 67};
    vector<int> nums2{2};

    findMedianSortedArrays(nums1, nums2);
}