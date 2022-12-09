#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> res;
        allCandidates(candidates, target, {}, res);
        return res;
    }

    void allCandidates(vector<int> &candidates, int target, vector<int> arr, vector<vector<int>> &res)
    {
        int sum = 0;
        for (int i : arr)
            sum += arr[i];
        if (target == sum)
        {
            res.push_back(arr);
            return;
        }
        if (sum > target)
        {
            return;
        }

        for (int i = 0; i < candidates.size(); i++)
        {
            if (sum + candidates[i] < target)
            {
                arr.push_back(i);
                allCandidates(candidates, target, arr, res);
                arr.pop_back();
            }
        }
    }
};

int main()
{
    vector<int> candidates{2, 3, 5};
    int target = 8;
    Solution s;

    vector<vector<int>> res = s.combinationSum(candidates, target);

    for (auto i : res)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }

        cout << endl;
    }
}