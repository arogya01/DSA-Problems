#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int numDivisible(int N, vector<int> arr)
{
    int count = 0;
    for (int i = 0; i < (int)arr.size() - 1; i++)
    {
        if ((arr[i] + arr[i + 1]) % N == 0)
        {
            count++;
        }
    }
    return count;
}

int largestAdjacentLCM(vector<int> arr)
{
    int largest = 0;
    for (int i = 0; i < arr.size() - 1; i++)
    {
        if (lcm(arr[i], arr[i + 1]) > largest)
        {
            largest = lcm(arr[i], arr[i + 1]);
        }
    }
    return largest;
}

int main()
{
    vector<int> sample{1, 2, 3, 4, 5};
    int n = 3;
    vector<int> test{1, 2, 3, 4};

    cout << numDivisible(n, sample) << endl;
    cout << numDivisible(2, sample) << endl;
    cout << largestAdjacentLCM(test) << endl;
}