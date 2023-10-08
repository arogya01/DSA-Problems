#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool comp(const vector<int> &a, const vector<int> &b)
{
    return a[0] < b[0];
}

class Solution
{
public:
    vector<int> getOrder(vector<vector<int>> &tasks)
    {

        int highestEqTime = 0;
        unordered_map<int, vector<int>> mp;

        sort(tasks.begin(), tasks.end(), comp);

        for (int i = 0; i < tasks.size(); i++)
        {
            if (tasks[i][0] > highestEqTime)
            {
                highestEqTime = tasks[i][0];
            }

            mp[tasks[i][0]].push_back(tasks[i][1]);
        }

        cout << "higest time" << highestEqTime << endl;
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int t = 1; t <= highestEqTime; t++)
        {
            if (mp.find(t) != mp.end())
            {
                for (auto i : mp[t])
                {
                    pq.push(i);
                }
            }
        }

        vector<int> ans;
        for (auto i : pq)
        {
            ans.push_back(i);
        }

        return ans;
    }
};

int main()
{
}