#include <iostream>
#include "IntArray.h"

using namespace std;

int main()
{
    IntArray array(10);

    for (int i{0}; i < 10; ++i)
        array[i] = i + 1;

    for (int i{0}; i < 10; ++i)
        cout << array[i] << endl;

    // Resize the array to 8 elements
    array.resize(8);

    // Insert the number 20 before element with index 5
    array.insertBefore(20, 5);

    for (int i{0}; i < 8; ++i)
        cout << array[i] << endl;
}