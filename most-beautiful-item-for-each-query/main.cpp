#include <iostream>

using namespace std;

class Solution
{
public:
    int search_for_el(vector<vector<int>> &items, int price)
    {

        int lo = 0;
        int hi = items.size() - 1;
        int queryAns = 0;
        int PRICE = 0;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;

            if (items[mid][PRICE] <= price)
            {
                queryAns = items[mid][1];
                lo = mid + 1;
            }
            else
                hi = mid - 1;
        }

        return queryAns;
    }

    vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries)
    {
        vector<int> ans;
        sort(items.begin(), items.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] < b[0]; });

        for (int i = 0; i < queries.size(); i++)
        {
            ans.push_back(search_for_el(items, queries[i]));
        }

        return ans;
    }
};

int main()
{
    vector<vector<int>> items{{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}};
    vector<int> queries { 1,
                          2,
                          3,
                          4,
                          5,
                          6 }
}