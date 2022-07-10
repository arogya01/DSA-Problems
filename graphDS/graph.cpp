#include <bits/stdc++.h>
using namespace std;

class Graph
{
    vector<vector<int>> m_grapharr;

public:
    Graph(vector<vector<int>> graph)
    {
        m_grapharr = graph;
    }

    void setMatrix(vector<vector<int>> graph)
    {
        m_grapharr = graph;
    }

    void DFS(int startNode)
    {
        stack<int> s1;
        vector<vector<int>>::iterator outer;
        vector<int>::iterator inner;
    }

    void printGraph()
    {
        vector<vector<int>>::iterator outer;
        vector<int>::iterator inner;

        for (outer = m_grapharr.begin(); outer != m_grapharr.end(); outer++)
        {
            for (inner = outer->begin(); inner != outer->end(); inner++)
            {
                cout << *inner;
            }

            cout << endl;
        }
    }

    vector<int> bfs(int startNode)
    {

        queue<int> q;
        vector<int> visited;
        q.push(startNode);
        while (!q.empty())
        {

            int front = q.front();
            q.pop();

            vector<int>::iterator itr;
            vector<int>::iterator check;

            check = std::find(visited.begin(), visited.end(), front);
            if (check == visited.end())
            {
                visited.push_back(front);
                for (itr = m_grapharr[front].begin(); itr != m_grapharr[front].end(); itr++)
                {
                    q.push(*itr);
                }
            }
        }

        return visited;
    }

    void dfs()
    {
    }
};

int main()
{

    vector<vector<int>> arrdouble{
        {},
        {4, 2},
        {1, 5, 7, 8},
        {4, 2, 10, 9},
        {1, 3},
        {6, 7, 2, 8},
        {5},
        {5, 8, 2},
        {2, 7, 5},
        {3},
        {3}};

    Graph s1(arrdouble);
    cout << "code is running fine." << endl;

    vector<int> yo = s1.bfs(2);

    vector<int>::iterator itr;

    for (itr = yo.begin(); itr != yo.end(); itr++)
    {
        cout << *itr << endl;
    }
}
