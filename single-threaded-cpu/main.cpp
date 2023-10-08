#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

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
        // for (auto i : pq)
        // {
        //     ans.push_back(i);
        // }

        return ans;
    }
};

class BetterSolution
{
public:
    vector<int> res;
    vector<int> getOrder(vector<vector<int>> &tasks)
    {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> valid;
        for (int i = 0; i < tasks.size(); i++)
        {
            pq.push({tasks[i][0], tasks[i][1], i});
        }
        long long timestamp = pq.top()[0];

        while (!pq.empty() || !valid.empty())
        {
            while (!pq.empty() && timestamp >= pq.top()[0])
            { // put all the valid tasks to the new pq
                auto curr = pq.top();
                pq.pop();
                valid.push({curr[1], curr[2]});
            }
            // use the smallest valid tasks
            if (valid.empty())
            {
                timestamp = pq.top()[0];
                continue;
            }
            auto validTop = valid.top();
            valid.pop();
            res.push_back(validTop[1]);
            timestamp += validTop[0];
        }

        return res;
    }
};

int main()
{
    vector<vector<int>> tasks{{1, 2}, {2, 4}, {3, 2}, {4, 1}};
    BetterSolution newS;

    vector<int> res{newS.getOrder(tasks)};

    for (auto i : res)
        cout << i;
}