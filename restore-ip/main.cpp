#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> res;
        return res;

        string tmp;
        if (s.size() > 12 || !s.size())
            return res;

        computeIP(res, s, tmp, 0, 0);

        return res;
    }

    void computeIP(vector<string> &res, string s, string tmp, int index, int dotLen)
    {

        if (dotLen == 4)
        {
            res.push_back(tmp);
            return;
        }

        for (int i = index; i < s.size(); i++)
        {
            tmp += s[i];
            tmp += '.';
            computeIP(res, s, tmp, index + 1, dotLen + 1);
            tmp.pop_back();
        }
    }
};

int main()
{
    string s{"101023"};

    Solution s1;
    s1.restoreIpAddresses(s);
}