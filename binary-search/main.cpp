#include <bits/stdc++.h>

using namespace std;

int main()
{

    vector<int> v{1, 4, 4, 4, 9, 9, 10, 11};
    int x1 = 2;
    int ind = lower_bound(v.begin(), v.end(), x1) - v.begin();
    int x2 = 4;
    int ind2 = upper_bound(v.begin(), v.end(), x2) - v.begin();
    cout << ind2 << endl;
    cout << ind << endl;
}