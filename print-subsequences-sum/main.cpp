#include <iostream>
#include <vector>

using namespace std;

void printSubsquencesSum(int index, vector<int> arr, int sum, vector<int> result)
{

    if (index == arr.size())
    {
        return;
    }

    result.push_back(arr[index]);
    index++;
    printSubsquencesSum(index, arr, sum, result);
    int tempSum = 0;
    for (int i : result)
    {
        tempSum += i;
    }
    if (sum == tempSum)
    {
        for (int i : result)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    result.pop_back();
    printSubsquencesSum(index, arr, sum, result);
}

int main()
{
    vector<int> arr = {1, 2, 1, 3, 4, 1, 2};
    int k = 4;
    vector<int> result;
    // for this the sum would be
    //  [1,2] [2,1]

    printSubsquencesSum(0, arr, k, result);
}