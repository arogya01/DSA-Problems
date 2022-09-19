#include <bits/stdc++.h>

using namespace std;

int trap(vector<int> &height)
{
    int left = 0, right = height.size() - 1, level = 0, water = 0;

    while (left < right)
    {
        int lower = height[height[left] < height[right] ? left++ : right--];
        level = max(level, lower);
        water += level - lower;
    }

    return water;
}

int main()
{
    vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    int res = trap(height);

    cout << res;
}