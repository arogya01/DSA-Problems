#include <bits/stdc++.h>

using namespace std;

struct comp
{
    bool operator()(int const &i, int const &j) const
    {
        return i > j;
    }
};

class Solution
{
public:
    bool makesquare(vector<int> &matchsticks)
    {
        bool ans = false;
        sort(begin(matchsticks), end(matchsticks), comp());
        return compute(matchsticks[0], matchsticks, 0, 0);
    }

    bool compute(int &sideLen, vector<int> &arr, int count, int index)
    {
        if (count == 4 && arr.size() == 0)
        {
            return true;
        }

        int el = arr[index];
        int diff = sideLen - el;

        if (diff == 0)
        {
            arr.erase(arr.begin() + index);
            compute(sideLen, arr, count + 1, 0);
        }

        // let's say the diff is whatever, alright, but I'm sure that you'll get it down the pipeline right. yups.

        for (int i = 0; i < arr.size(); i++)
        {
            if (diff == 0)
                break;
            if (arr[i] < diff)
            {
                diff -= arr[i];
                arr.erase(arr.begin() + i);
            }
        }

        if (diff == 0)
        {
            arr.erase(arr.begin() + index);
            compute(sideLen, arr, count + 1, 0);
        }

        return false;
    }
};

int main()
{
    vector<int> mt{8, 6, 6, 5, 3, 2, 1, 1};

    Solution s1;
    cout << s1.makesquare(mt);
}