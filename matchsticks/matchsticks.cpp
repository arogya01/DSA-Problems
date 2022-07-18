#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool makesquare(vector<int> &matchsticks)
{

    // true - if you can create the square.

    if (matchsticks.size() < 4)
    {
        return false;
    }
    unordered_map<int, int> mp;

    if (matchsticks.size() % 4 == 0)
    {
        int temp;
        unordered_map<int, int> mp1;

        for (int i = 0; i < matchsticks.size(); i++)
        {

            if (mp1.find(matchsticks[i]) != mp1.end())
            {
                int temp = 0;
                temp = mp1[matchsticks[i]];
                mp1[matchsticks[i]] = ++temp;
            }
            else
            {
                mp1[matchsticks[i]] = 1;
            }
        }

        for (auto x : mp1)
        {
            cout << x.first << "  " << x.second << endl;
            if (x.second % 4 != 0)
            {
                return false;
            }
        }
    }
    else
    {
        for (int i = 0; i < matchsticks.size(); i++)
        {

            if (matchsticks[i] != matchsticks[i + 1] && matchsticks[i] > matchsticks[i + 1])
            {

                if (matchsticks[i] % matchsticks[i + 1] != 0)
                {
                    return false;
                }
            }

            if (mp.find(matchsticks[i]) != mp.end())
            {
                int temp = 0;
                temp = mp[matchsticks[i]];
                mp[matchsticks[i]] = ++temp;
            }
            else
            {
                mp[matchsticks[i]] = 1;
            }
        }

        for (auto x : mp)
        {
            cout << x.first << "  " << x.second << endl;
            if (x.second % 2 != 0 && x.second != 3 & x.second != 1)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
}