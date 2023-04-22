#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    string removeStars(string s)
    {
        string ans;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '*')
            {
                cout << s << endl;
                s.erase(s.begin() + i);
                s.erase(s.begin() + i - 1);
                i = i - 2;
                cout << "after removal " << s << endl;
            }
        }

        cout << s << endl;
        return s;
    }
};

int main()
{
    Solution s;
    string str = "erase*****";
    s.removeStars(str);
    return 0;
}
