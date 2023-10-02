#include <iostream>
#include <vector>

using namespace std;

class MaxHeap
{
    vector<int> max_heap;
    int cap;

public:
    MaxHeap(int n);
};

int main()
{
    MaxHeap h(9);

    h.insertKey(3);
    h.insertKey(2);
    h.insertKey(1);
    h.insertKey(15);
    h.insertKey(24);
    h.insertKey(31);

    h.printHeap();
}