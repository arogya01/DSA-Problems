#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class BfsGraph
{
    int numVertices;
    vector<int> *adjList;

public:
    BfsGraph(int vertices)
    {
        numVertices = vertices;
        adjList = new vector<int>[vertices]; // creating an array of vertices size...
    }

    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void traverse(int startVertex)
    {
        queue<int> q;
        vector<bool> visited(numVertices, false);

        visited[startVertex] = true;

        while (!q.empty())
        {
            int vertex = q.front();

            cout << vertex << " ";
            q.pop();

            for (int i = 0; i < adjList[vertex].size(); i++)
            {
                int adjVertex = adjList[vertex][i];

                if (!visited[adjVertex])
                {
                    q.push(adjVertex);
                    visited[adjVertex] = true;
                }
            }
        }
    }
};

int main()
{
    BfsGraph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    g.traverse(0);

    return 0;
}