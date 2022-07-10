#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

bool isInterleave(string s1, string s2, string s3)
{
    unordered_map<string, int> mp;

    if (s1.size() == 0 && s2.size() == 0 && s3.size() == 0)
    {
        return true;
    }

    if (s3.size() > s1.size() + s2.size())
    {
        return false;
    }

    for (int i = 0; i < s1.size(); i++)
    {
        string temp = "";
        for (int j = 0; j <= i; j++)
        {
            temp += s1[j];
        }
        mp[temp] = temp.size();
    }

    for (int i = 0; i < s2.size(); i++)
    {
        string temp = "";
        for (int j = 0; j <= i; j++)
        {
            temp += s2[j];
        }
        mp[temp] = temp.size();
    }

    for (auto x : mp)
    {
        cout << x.first << " " << x.second << endl;
    }

    int stringLen = 0;
    for (int i = 0; i <= s3.size(); i++)
    {
        string temp;
        for (int j = 0; j <= i; j++)
        {
            temp += s3[j];
        }

        if (mp.find(temp) != mp.end())
        {
            cout << temp << endl;
            stringLen += mp[temp];
        }
    }

    cout << stringLen << s3.size();
    return true;
}

int main()
{
    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";
    bool result = isInterleave(s1, s2, s3);

    cout << endl
         << result;
}