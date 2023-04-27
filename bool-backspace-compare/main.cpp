#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

class Solution
{
public:
    bool backspaceCompare(string s, string t)
    {

        stack<char> s1;
        stack<char> s2;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '#')
            {
                s1.pop();
            }
            else
                s1.push(s[i]);
        }

        for (int i = 0; i < t.size(); i++)
        {
            if (t[i] == '#')
            {
                s2.pop();
            }
            else
                s2.push(t[i]);
        }

        string newStr1;
        string newStr2;
        while (!s1.empty())
        {
            newStr1 += s1.top();
            s1.pop();
        }

        while (!s2.empty())
        {
            newStr2 += s2.top();
            s2.pop();
        }

        cout << "newstr1 is: " << newStr1 << endl
             << newStr2 << endl;
        return newStr1 == newStr2;
    }
};

int main()
{
    string s{"ab#c"}, t{"ad#c"};
    Solution s1;
    cout << s1.backspaceCompare(s, t);
}