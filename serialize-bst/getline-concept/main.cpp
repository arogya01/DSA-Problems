#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    string line("this is a line");
    string item;
    while (getline(line, item, '-'))
    {
        cout << item << endl;
    }
}