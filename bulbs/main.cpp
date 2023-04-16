#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int bulbs(vector<int> &A);
};

int Solution::bulbs(vector<int> &A)
{
    // need to find the minimum number of switches, right?
    int zerosCount = 0;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == 0)
        {
            zerosCount++;
        }
    }
    cout << zerosCount << endl;
    return zerosCount + (A.size() - zerosCount);
}

int main()
{
    vector<int> A = {0, 1, 0};
    Solution s;
    cout << s.bulbs(A);
}