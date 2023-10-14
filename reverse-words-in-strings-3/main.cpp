#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {
        stack<char> st;

        for (auto i : s)
        {
            st.push(i);
        }

        vector<string> res;
        string result;
        while (!st.empty())
        {
            auto topEl = st.top();
            if (topEl == ' ')
            {
                res.push_back(result);
                result = "";
                st.pop();
                continue;
            }
            else
            {
                result += topEl;
                st.pop();
            }
        }
        res.push_back(result);
        string newRes;
        for (int i = res.size() - 1; i >= 0; i--)
        {
            newRes += res[i];
            if (i != 0)
                newRes += " ";
        }

        return newRes;
    }
};

int main()
{
    string sample = "Let's take LeetCode contest";
    Solution s;
    cout << s.reverseWords(sample);
}