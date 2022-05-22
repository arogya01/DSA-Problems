#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool isAnagram(string s, string t)
{
    unordered_map<char, int> mp;
    unordered_map<char, int> mp2;

    if (s.length() != t.length())
    {
        return false;
    }

    for (int i = 0; i < s.length(); i++)
    {
        cout << s[i];
        if (mp.find(s[i]) != mp.end())
        {
            int prev = mp[s[i]];
            prev++;
            mp[s[i]] = prev;
        }
        else
        {
            mp[s[i]] = 1;
        }
    }

    for (int i = 0; i < t.length(); i++)
    {
        // int ch = std::count(s.begin(),s.end() , s);

        // cout<<"the char count is: "<<ch<<endl;

        if (mp2.find(t[i]) != mp2.end())
        {
            int prev = mp2[t[i]];
            prev++;
            mp2[t[i]] = prev;
        }
        else
        {
            mp2[t[i]] = 1;
        }
    }

    for (auto x : mp2)
    {
        cout << x.first << " " << x.second << endl;
        if (mp.find(x.first) != mp.end())
        {
            if (x.second != mp[x.first])
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

int main()
{
    string s = "ab";
    string t = "a";
    bool result = isAnagram(s, t);
    cout << result << endl;
}
