#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
    {
        vector<int> res;
        int temp;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                temp += compute();
            }
            res.push_back(temp);
        }
    }
};