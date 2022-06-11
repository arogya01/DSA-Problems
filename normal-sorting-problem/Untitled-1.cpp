#include <iostream>
#include <vector>
#include <algorithm>

// we've an array, three types of elements
// [0,1,2]
// sort that array

// [1,0,0,0,2,1]

using namespace std;

int main()
{
    vector<int> arr{1, 2, 0, 0, 2, 2, 0};

    // use a for loop, count the number of 0 , 1 & 2. then, we can create new arr,
    int end = arr.size() - 1;
    int start = 0;

    while (start <= end)
    {
        if (arr[start] > arr[start + 1])
        {
            int temp = arr[start + 1];
            arr[start + 1] = arr[start];
            arr[start] = temp;

            start++;
        }

        if (arr[end] < arr[end - 1])
        {
            int temp = arr[end - 1];
            arr[end - 1] = arr[end];
            arr[end] = temp;
            end--;
        }

        if (arr[start] > arr[end])
        {
            int temp = arr[end];
            arr[end] = arr[start];
            arr[start] = temp;
        }

        start++;
        end--;
    }

    for (int i = 0; i < arr.size(); i++)
    {
        cout << " " << arr[i];
    }
}
