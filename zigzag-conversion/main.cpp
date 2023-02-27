#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;
        string res;
        vector<vector<char>> char2d(numRows, vector<char>(s.size()));
        int cols;
        for (int i = 0; i < s.size(); i += numRows)
        {
            if (cols % 2 == 0)
            {
                for (int j = 0; j < numRows; j++)
                {
                    char2d[j].insert(char2d[j].begin() + cols, s[i]);
                }
                cols++;
            }
            else
            {
                for (int x = numRows - 1; x > 0; x++)
                {
                    char2d[x].insert(char2d[x].begin() + cols, s[i]);
                    cols++;
                }
            }
        }

        for (auto x : char2d)
        {
            for (auto y : x)
            {
                cout << y << " ";
            }
            cout << endl;
        }

        return res;
    }
};

int main()
{
    cout << "what";
}
