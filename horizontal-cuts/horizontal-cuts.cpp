#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxArea(int h, int w, vector<int> &horizontalCuts, vector<int> &verticalCuts)
{
    long long horidiff = 0;
    long long verdiff = 0;
    long long maxarea = 0;
    const unsigned int M = 1000000007;

    sort(horizontalCuts.begin(), horizontalCuts.end());
    sort(verticalCuts.begin(), verticalCuts.end());

    if (horizontalCuts.size() == 1)
    {
        if (h - horizontalCuts[0] > horizontalCuts[0])
        {
            horidiff = h - horizontalCuts[0];
        }
        else
            horidiff = horizontalCuts[0];
    }
    else
    {

        for (long long i = 0; i < horizontalCuts.size() - 1; i++)
        {
            if (horizontalCuts[i + 1] - horizontalCuts[i] > horidiff)
            {
                horidiff = horizontalCuts[i + 1] - horizontalCuts[i];
            }
        }
    }

    if (h - horizontalCuts.back() > horidiff)
    {

        horidiff = h - horizontalCuts.back();
    }

    if (verticalCuts.size() == 1)
    {
        if (w - verticalCuts[0] > verticalCuts[0])
        {
            verdiff = w - verticalCuts[0];
        }
        else
            verdiff = verticalCuts[0];
    }
    else
    {

        for (long long i = 0; i < verticalCuts.size() - 1; i++)
        {
            if (verticalCuts[i + 1] - verticalCuts[i] > verdiff)
            {
                verdiff = verticalCuts[i + 1] - verticalCuts[i];
            }
        }
    }

    if (w - verticalCuts.back() > verdiff)
    {
        verdiff = w - verticalCuts.back();
    }

    maxarea = horidiff * verdiff;

    return (maxarea % M);
}

int main()
{

    int h = 1000000000;
    int w = 1000000000;
    vector<int> horizontalCuts{2};
    vector<int> verticalCuts{2};

    // long long res = maxArea(h, w, horizontalCuts, verticalCuts);
    // cout << res;

    int a = 9;
    int b = 2;

    int d = (int)a / b;
    cout << d;
}