#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Solution
{
public:
    string customSortString(string order, string s)
    {

        map<char, int> mp;
        int count = 1;
        for (auto i : order)
        {
            mp[i] = count;
            count++;
        }

        for (int i = 0; i < s.size() - 1; i++)
        {
            if (mp.find(s[i]) != mp.end() && mp.find(s[i] + 1) != mp.end() && mp[s[i]] > mp[s[i + 1]])
            {
                char temp = s[i];
                s[i] = s[i + 1];
                s[i + 1] = temp;
            }
            else
            {
                char temp = s[i];
                s[i] = s[i + 1];
                s[i + 1] = temp;
            }
        }

        return s;
    }
};

int main()
{
    string s{"abcd"};
    string order{"cba"};

    Solution sr;
    cout << sr.customSortString(order, s);
}