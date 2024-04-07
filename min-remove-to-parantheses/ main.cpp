#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
    string minRemoveToMakeValid(string s)
    {

        stack<int> st;
        string ans;
        for (int i = 0; i < s.size(); i++)
        {
            st.push(s[i]);
        }

        bool loop = true;

        while (!st.empty())
        {
            int top = st.top();
            st.pop();
            if (loop == true && top == ')')
            {
                ans += top;
                loop = false;
            }
            else if (loop == false && top == '(')
            {
                ans += top;
                loop = true;
            }

            if (islower(top))
                ans += top;
        }

        return ans;
    }
};

int main()
{
    string s{"lee(t(c)o)de)"};

    Solution st;
    st.minRemoveToMakeValid(s);
}