// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;

// Function to return the required digit
int find_digit(string s, int n)
{

    // To store the position of the first
    // numeric digit in the string
    int first_digit = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            first_digit = i;
            break;
        }
    }
    first_digit++;

    // To store the length of the
    // string without the numeric
    // digits in the end
    int s_len = first_digit;

    // pw stores the current power of 10
    // and num is to store the number
    // which is appended in the end
    int num = 0, pw = 1;
    int i = n - 1;
    while (i >= 0)
    {

        // If current character is
        // a numeric digit
        if (s[i] >= '0' && s[i] <= '9')
        {

            // Get the current digit
            int digit = s[i] - '0';

            // Build the number
            num = num + (pw * digit);

            // If number exceeds the length
            if (num >= s_len)
                return -1;

            // Next power of 10
            pw = pw * 10;
        }
        i--;
    }

    // Append 0 in the end
    num = num * 10;

    // Required number that must be added
    int req = s_len - num;

    // If number is not a single digit
    if (req > 9 || req < 0)
        return -1;
    return req;
}

// Driver code
int main()
{
    string s;

    cin >> s;
    int n = s.length();

    cout << find_digit(s, n);

    return 0;
}
