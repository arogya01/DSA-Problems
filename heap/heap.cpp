#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// okay, so this will be divided between min-heap and max-heap. both of them will have different sorts of functions right.

void swap(int *x, int *y);

class MinHeap
{
    int *harr;
    int capacity;
    int heap_size;

public:
    MinHeap(int capacity);
    void minHeapify(int);
    int parent(int i) { return (i - 1) / 2; }

    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    int extractMin();

    void decreaseKey(int i, int new_val);

    int getMin() { return harr[0]; }

    void deleteKey(int i);
    void insertKey(int k);
    void printHeap()
    {

        for (int i = 0; i < heap_size; i++)
        {
            cout << harr[i] << endl;
        }
    }
};

MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        cout << "\n overflow: could not insertKey \n";
        return;
    }

    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// oh okay, so in extractMin, we're taking out the minimum value and then arranging in the pattern so that it doesn't violate the property. (interesting).
int MinHeap::extractMin()
{
    if (heap_size <= 0)
    {
        return INT_MAX;
    }

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    minHeapify(0);

    return root;
}

// minheapify essentially helps us in arranging the elements to respect the heap property. it considers that the sub-nodes are already heapified.
void MinHeap::minHeapify(int i)
{

    int l = left(i);
    int r = right(i);

    int smallest = i;

    if (l < heap_size && harr[l] < harr[i])
    {
        smallest = l;
    }
    if (r < heap_size && harr[r] < harr[smallest])
    {
        smallest = r;
    }

    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        minHeapify(smallest);
    }
}

void swap(int *x, int *y)
{
    int temp = *x;

    *x = *y;
    *y = temp;
}

int main()
{
    MinHeap h(9);

    h.insertKey(3);
    h.insertKey(2);
    h.insertKey(1);
    h.insertKey(15);
    h.insertKey(24);
    h.insertKey(31);

    h.printHeap();

    // how do you print this thing, it's actually in reality just an array..
}