#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#define __cpluscplus
using std::cout, std::string, std::vector, std::endl;

bool isPalindrome(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    string::iterator s1;
    string::iterator s2;
    // s.erase(remove(s.begin(), s.end(), ' '), s.end());
    // s.erase(remove(s.begin(), s.end(), ','), s.end());
    // s.erase(remove(s.begin(), s.end(), ':'), s.end());

    s.erase(std::remove_if(s.begin(), s.end(), [](auto ch)
                           { return !(ch >= 97 && ch <= 122) && !(ch >= 48 && ch <= 57); }),
            s.end());
    s1 = s.begin();
    s2 = s.end() - 1;
    cout << s << endl;
    while (s1 < s2)
    {

        if (!(*s1 >= 97 && *s1 <= 122) && !(*s1 >= 48 && *s1 <= 57))
        {
            cout << *s1;
            cout << "yes" << endl;
            s1++;
        }
        else if (!(*s2 >= 97 && *s2 <= 122) && !(*s1 >= 48 && *s1 <= 57))
        {
            s2--;
        }

        if (*s1 != *s2)
        {
            cout << endl
                 << *s1 << " " << *s2;
            return false;
        }
        s1++;
        s2--;
    }

    return true;
}

int main()
{
    string s = "......a.....";
    bool res = isPalindrome(s);
    cout << res;
}