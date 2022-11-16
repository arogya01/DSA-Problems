#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    void comb(vector<int> &candidates, int target, vector<vector<int>> &res, vector<int> &r, int i)
    {

        if (target == 0)
        {
            res.push_back(r);
            return;
        }

        if (i >= candidates.size())
        {
            return;
        }

        r.push_back(candidates[i]);
        comb(candidates, target - candidates[i], res, r, i + 1);

        r.pop_back();
        comb(candidates, target, res, r, i + 1);
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> r;
        comb(candidates, target, res, r, 0);

        return res;
    }
};

int main()
{
    vector<int> candidates{1, 2, 2, 2, 5};
    int target = 5;
    Solution s1;
    vector<vector<int>> res = s1.combinationSum2(candidates, target);

    for (auto i : res)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}