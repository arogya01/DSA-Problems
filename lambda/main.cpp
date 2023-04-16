#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void abssort(float *x, unsigned n)
{
    std::sort(x, x + n, [](float a, float b)
              { return abs(a) < abs(b); });
}

int main()
{
    float x[] = {1.0, -2.0, 3.0, -4.0, 5.0, -6.0};
    abssort(x, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << x[i] << " ";
    }
    return 0;
}