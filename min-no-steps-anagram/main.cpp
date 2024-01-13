#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int minSteps(string s, string t)
    {
        map<char, int> count;
        for (auto i : s)
        {
            if (count.find(i) != count.end())
            {
                count[i]++;
            }
            else
                count[i] = 1;
        }

        int finalAns = 0;

        for (auto i : t)
        {
            if (count.find(i) != count.end())
            {
                if (count[i] == 0)
                    finalAns++;
                count[i] = count[i] - 1;
            }
            else
                finalAns++;
        }

        return finalAns;
    }
};

int main()
{
    string a{"leetcode"};
    string b{"practice"};

    Solution s;
    s.minSteps(a, b);
}