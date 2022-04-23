#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;
#include <algorithm>

/***
Top K frequent elements, in here basically we've to calculate the k most frequent elements.

Sample testcases:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Input: nums = [1], k = 1
Output: [1]
***/

/***
  Used Hashmap to store the element to frequency
  then, used a vector to compare that
 seems like it took O(n) time
 ***/

bool cmp(pair<int, int> &a, pair<int, int> &b)
{
    return b.second < a.second;
}

void sortIt(unordered_map<int, int> &m)
{

    vector<pair<int, int>> A;

    for (auto &it : m)
    {
        A.push_back(it);
    }

    sort(A.begin(), A.end(), cmp);

    for (auto &it : A)
    {

        cout << it.first << ' '
             << it.second << endl;
    }
}

class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> table;
        vector<int> result{};
        int highest = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (table.find(nums[i]) != table.end())
            {
                int prevValue = table[nums[i]];
                prevValue++;
                if (prevValue > highest)
                {
                    highest = prevValue;
                }
                table[nums[i]] = prevValue;
            }
            else
            {
                table.insert(make_pair(nums[i], 1));
            }
        }

        vector<pair<int, int>> A;

        for (auto &it : table)
        {
            A.push_back(it);
        }

        sort(A.begin(), A.end(), cmp);

        for (auto &it : A)
        {

            cout << it.first << ' '
                 << it.second << endl;
        }

        for (int i = 0; i < A.size(); i++)
        {
            if (i == k)
            {
                break;
            }
            result.push_back(A[i].first);
        }

        return result;
    }
};

int main()
{
    Solution result;
    vector<int> nums{1, 1, 1, 2, 2, 3, 3, 6, 8, 9, 8, 98, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    int k = 4;
    vector<int> res = result.topKFrequent(nums, k);
    cout << "--- the result is " << endl;
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
}