#include <iostream>

using namespace std;

class Solution
{
public:
    int peakIndexInMountainArray(vector<int> &arr)
    {
        return std::distance(arr.begin(), std::max_element(arr.begin(), arr.end()));
    }
};

int main()
{
    vector<int> a1{0, 10, 5, 2};
    Solution s1;
    s1.peakIndexInMountainArray(a1);
}