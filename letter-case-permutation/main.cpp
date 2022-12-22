#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    void compute(vector<string> &res, string &s, string newStr, int i)
    {
        if (newStr.size() == s.size())
        {
            res.push_back(newStr);
            return;
        }

        if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9')
        {
            newStr += s[i];
            compute(res, s, newStr, i + 1);

            int c = newStr[i];
            if (islower(c))
                newStr[i] = toupper(c);
            else if (isupper(c))
                newStr[i] = tolower(c);

            compute(res, s, newStr, i + 1);
        }
        else
        {
            newStr += s[i];
            compute(res, s, newStr, i + 1);
        }
    }

    vector<string> letterCasePermutation(string s)
    {
        vector<string> newarr;
        compute(newarr, s, "", 0);
        return newarr;
    }
};

int main()
{
    string s = "a1z";

    Solution s1;
    vector<string> res;
    res = s1.letterCasePermutation(s);

    for (string i : res)
    {
        cout << i << endl;
    }
}