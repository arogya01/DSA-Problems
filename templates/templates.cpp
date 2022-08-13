#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
// it's a space to discuss about how templates work, and learning more about function and class templates.
using namespace std;

// Function Templates
template <typename T>

void swap(T &a, T &b)
{
    T temp{a};
    a = b;
    b = temp;
}

int main()
{

    int a = 2;
    int c = 5;

    // string str1 = "someti";
    // string str2 = "fuck";
    // swap(a, c);
    // swap(str1, str2);

    // std::cout << a << c;

    unordered_map<int, int> mp;

    mp[1] = 2;
    mp[3] = 4;

    for (auto &[x, y] : mp)
    {
        cout << x << " " << y << endl;
    }
}