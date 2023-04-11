#include <bits/stdc++.h>

using namespace std;

int main()
{
    set<int> s;

    for (int i = 0; i < 100000; i++)
    {
        s.insert(s.end(), i);
    }

    for (auto i : s)
    {
        cout << i << " ";
    }
}