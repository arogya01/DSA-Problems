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

    // essentially, what're doing in DFS is start exploring the adjacent nodes and keep exploring them, don't stop and push the other elements into the stack.
    vector<int> dfs(int startNode)
    {
        stack<int> st;
        vector<int> visited;

        // visited.push_back(startNode);
        st.push(startNode);
        while (!st.empty())
        {

            int temp = st.top();
            st.pop();
            vector<int>::iterator itr;
            vector<int>::iterator check;
            check = find(visited.begin(), visited.end(), temp);
            if (check == visited.end())
            {
                // cout << temp << " ";
                visited.push_back(temp);
                for (itr = m_grapharr[temp].begin(); itr != m_grapharr[temp].end(); itr++)
                {
                    st.push(*itr);
                }
            }
        }

        return visited;
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

    vector<vector<int>> arr{
        {},
        {2, 5},
        {1, 3, 4},
        {2},
        {2, 6},
        {1},
        {4}};
    Graph s1(arrdouble);
    Graph s2(arr);

    cout << "code is running fine." << endl;

    vector<int> yo = s1.bfs(2);
    vector<int>::iterator itr;

    // s1.dfs(2);
    vector<int> res = s2.dfs(1);
    for (itr = res.begin(); itr != res.end(); itr++)
    {
        cout << *itr << " ";
    }
    cout << endl;
    for (itr = yo.begin(); itr != yo.end(); itr++)
    {
        cout << *itr << endl;
    }
}
