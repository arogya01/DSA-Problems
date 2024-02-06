#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int initColor = image[sr][sc];
        dfsTraversal(image, sr, sc, color, initColor);

        for (int i = 0; i < image.size(); i++)
        {
            for (int j = 0; j < image[i].size(); i++)
            {
                cout << j << " ";
            }
            cout << endl;
        }

        return image;
    }

    void dfsTraversal(vector<vector<int>> &image, int x, int y, int &newColor, int &initColor)
    {
        if (image[x][y] == newColor)
            return;
        image[x][y] = newColor;
        int n1 = image.size();
        int n2 = image[0].size();
        if (x > 0 && image[x - 1][y] == initColor)
            dfsTraversal(image, x - 1, y, newColor, initColor);
        if (y > 0 && image[x][y - 1] == initColor)
            dfsTraversal(image, x, y - 1, newColor, initColor);
        if (x < n1 - 1 && image[x + 1][y] == initColor)
            dfsTraversal(image, x + 1, y, newColor, initColor);
        if (y < n2 - 1 && image[x][y + 1] == initColor)
            dfsTraversal(image, x, y + 1, newColor, initColor);
    }
};

int main()
{
    vector<vector<int>> image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};

    Solution s;
    s.floodFill(image, 1, 1, 2);
}