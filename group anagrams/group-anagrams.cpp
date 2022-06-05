#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> mp;
        for (string s : strs)
        {
            string sorted = s;
            sort(sorted.begin(), sorted.end());
            mp[sorted].push_back(s);
        }

        unordered_map<string, vector<string>>::iterator o = mp.begin();
        while (o != mp.end())
        {
            result.push_back(o->second);
            o++;
        }

        return result;
    }
};

int main()
{
    vector<string> a{"eat", "tea", "tan", "ate", "nat", "bat"};

    Solution s1;
    s1.groupAnagrams(a);
}