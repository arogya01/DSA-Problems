#include <bits/stdc++.h>

using namespace std;

int main()
{

    int n, m;

    cin >> n >> m;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    int n1, n2;
    for (int i = 0; i < m; i++)
    {
        cout << "enter the nodes that have a edge: " << endl;
        cin >> n1 >> n2;
        adj[n1][n2] = 1;
        adj[n2][n1] = 1;
    }
}