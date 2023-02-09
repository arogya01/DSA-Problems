#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int characterReplacement(string s, int k)
    {
        int i = 0, j = 0, maxFreq = 0, maxLen = 0;
        unordered_map<char, int> mp; // storing the frequency of all the elements
        while (j < s.size())
        {                                     // format of sliding window
            mp[s[j]]++;                       // updating our hash map
            maxFreq = max(maxFreq, mp[s[j]]); // storing element with highest frequency
            if ((j - i + 1) - maxFreq <= k)
            { // it our answer coz we can delete at most k element
                maxLen = max(maxLen, j - i + 1);
                j++; // why increment coz need highest length which is possible
            }
            else if ((j - i + 1) - maxFreq > k)
            {
                while ((j - i + 1) - maxFreq > k)
                {
                    mp[s[i]]--; // we can replace more than k elements than we have to shrink our string
                    i++;
                }
                j++; // slide the window
            }
        }
        return maxLen;
    }
};

int main()
{
    string exp{"ABABBA"};
    Solution s1;
    cout << s1.characterReplacement(exp, 2);
}