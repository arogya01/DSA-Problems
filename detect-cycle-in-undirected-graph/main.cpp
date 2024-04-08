#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

bool detectCycle(vector<vector<int>> &graph, int n)
{
    queue<int> q;
    unordered_set<int> visited;

    for (int i = 0; i < n; i++)
    {
        if (visited.count(i) == 0)
        {
            q.push(i);
            visited.insert(i);

            while (!q.empty())
            {
                int curr = q.front();
                q.pop();

                for (int neighbor : graph[curr])
                {
                    if (visited.count(neighbor) == 0)
                    {
                        q.push(neighbor);
                        visited.insert(neighbor);
                    }
                    else
                    {
                        // If a node is already visited, it means we have found a cycle
                        return true;
                    }
                }
            }
        }
    }

    // No cycle found
    return false;
}

int main()
{
    int n = 6;
    vector<vector<int>> graph = {
        {1, 2},
        {0, 2, 3},
        {0, 1, 3, 4},
        {1, 2, 4, 5},
        {2, 3, 5},
        {3, 4}};

    if (detectCycle(graph, n))
    {
        cout << "Cycle detected" << endl;
    }
    else
    {
        cout << "No cycle detected" << endl;
    }

    return 0;
}