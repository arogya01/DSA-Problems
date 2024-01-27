#include <iostream>
#include <vector>

using namespace std;

class DfsTraversal
{
    int numVertices;
    vector<int> *adjList;
    vector<int> visited;

public:
    DfsTraversal(int vertices)
    {
        numVertices = vertices;
        adjList = new vector<int>[vertices];
        visited = vector<int>(vertices, 0);
    }

    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void dfs(int vertex)
    {

        visited[vertex] = 1;
        for (auto i : adjList[vertex])
        {

            if (!visited[i])
            {
                cout << "current vertex is: " << i << endl;
                visited[i] = 1;
                dfs(i);
            }
        }
    }
};

int main()
{
    DfsTraversal s(9);

    s.addEdge(1, 2);
    s.addEdge(2, 1);
    s.addEdge(1, 3);
    s.addEdge(2, 5);
    s.addEdge(2, 6);
    s.addEdge(3, 7);
    s.addEdge(3, 4);
    s.addEdge(4, 8);
    s.addEdge(7, 8);

    s.dfs(1);
}