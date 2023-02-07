#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    bool splitString(string s)
    {
        int idx = 0;
        vector<long long int> v;
        return fun(s, idx, v);
    }

    long long int maxval = 99999999991; // 9999999998
    bool fun(string &s, int idx, vector<long long int> &v)
    {
        if (idx >= s.length())
        {
            if (v.size() >= 2)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    cout << v[i] << " ";
                }
                cout << endl;
                return true;
            }
            else
            {
                return false;
            }
        }

        long long int num = 0;
        string str = "";

        for (int i = idx; i < s.length(); i++)
        {
            char ch = s[i];

            num = (num * 10LL) + (ch - '0') + 0LL;
            str.push_back(ch);

            if (num >= maxval)
            {
                return false;
            }

            if (v.size() == 0)
            {
                v.push_back(num);
                if (fun(s, i + 1, v) == true)
                {
                    return true;
                }
                v.pop_back(); // backtracking
            }
            else if (v.size() > 0)
            {
                long long int currnum = num;
                long long int lastnum = v[v.size() - 1];

                if ((lastnum - currnum) == 1)
                {
                    v.push_back(num);
                    if (fun(s, i + 1, v) == true)
                    {
                        return true;
                    }
                    v.pop_back();
                }
            }
        }
        return false;
    }
};

int main()
{
    string s{"005043"};
    Solution s1;
    cout << s1.splitString(s);
}