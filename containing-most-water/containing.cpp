#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Question Link : https://leetcode.com/problems/container-with-most-water

int maxArea(vector<int> &height)
{

    int start = 0;
    int end = height.size() - 1;
    int maxVal = 0;
    while (start < end)
    {
        int tempVal = 0;

        if (height[start] < height[end])
        {
            // cout<< "end - start is "<< (end-start) <<" "<<height[start]<<endl;
            tempVal = (end - start) * height[start];
        }
        else
        {
            // cout<< "end - start is "<< (end-start) <<" "<<height[end]<<endl;

            tempVal = (end - start) * height[end];
        }

        if (maxVal < tempVal)
        {
            maxVal = tempVal;
        }

        if (height[start] > height[end])
            end--;
        else
            start++;
    }

    return maxVal;
}

int main()
{

    vector<int> height{1, 2, 8, 6, 3, 4};

    int result = maxArea(height);

    cout << result;
}