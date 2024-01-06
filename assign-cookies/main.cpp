#include <iostream>

using namespace std;

class Solution
{
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        int finalAns = 0;
        if (g == s)
            return g.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        for (int i = 0; i < g.size(); i++)
        {
            auto it = std::lower_bound(s.begin(), s.end(), g[i]);
            if (it != s.end())
            {
                *it = -1;
                finalAns++;
            }
        }
        return finalAns;
    }
};

int main()
{
}