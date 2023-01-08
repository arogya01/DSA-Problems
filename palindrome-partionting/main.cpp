#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> ret;
        if (s.empty())
            return ret;

        vector<string> path;
        dfs(0, s, path, ret);

        return ret;
    }

    void dfs(int index, string &s, vector<string> &path, vector<vector<string>> &ret)
    {
        if (index == s.size())
        {
            ret.push_back(path);
            return;
        }
        for (int i = index; i < s.size(); ++i)
        {
            if (isPalindrome(s, index, i))
            {
                path.push_back(s.substr(index, i - index + 1));
                dfs(i + 1, s, path, ret);
                path.pop_back();
            }
        }
    }

    bool isPalindrome(const string &s, int start, int end)
    {
        while (start <= end)
        {
            if (s[start++] != s[end--])
                return false;
        }
        return true;
    }
};

int main()
{
    string s{"aab"};

    Solution s1;
    vector<vector<string>> str = s1.partition(s);

    for (auto i : str)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}