#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// this solution of mine ran for 77/80 test cases.
// now the caveat is the edge case is too big in the terms of vertices that it's just too hard for me to comprehend.
bool isOddLength(vector<vector<int>> &graph)
{

    bool result = true;
    queue<int> q;
    vector<bool> visited;
    visited.resize(graph.size(), false);
    vector<int> nodeColors;
    nodeColors.resize(graph.size(), -1);
    int n = graph.size();
    for (int i = 0; i < n; i++)
    {
        if (nodeColors[i] != -1)
            continue;

        q.push(i);
        nodeColors[i] = 1;

        while (!q.empty())
        {

            int front = q.front();
            q.pop();

            vector<int>::iterator itr;

            if (!visited[front])
            {
                visited[front] = true;

                for (itr = graph[front].begin(); itr != graph[front].end(); itr++)
                {
                    q.push(*itr);

                    if (nodeColors[*itr] != -1)
                    {
                        if (nodeColors[*itr] != (1 - nodeColors[front]))
                        {
                            return false;
                        }
                    }
                    else
                    {
                        nodeColors[*itr] = 1 - nodeColors[front];
                    }
                }
            }
        }
    }

    return result;
}

class Graph
{

    vector<vector<int>> graph;

public:
    bool isPartite(vector<vector<int>> &g)
    {
        bool result = isOddLength(g);

        return result;
    }

    void insertNode() {}
};

int main()
{
    vector<vector<int>> grpharr{{2, 4}, {2, 3, 4}, {0, 1}, {1}, {0, 1}, {7}, {9}, {5}, {}, {6}, {12, 14}, {}, {10}, {}, {10}};

    bool result = isOddLength(grpharr);

    cout << result;
}