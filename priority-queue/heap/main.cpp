#include <iostream>
#include <vector>

using namespace std;

// a heap is a data structure and not an abstract data type...
// it is a complete binary tree
// it is a tree where all the levels are filled except the last level
// the last level is filled from left to right

// a heap is a maximally efficient implementation of a priority queue
class MaxHeap
{
private:
    vector<int> heap;
    void sift_up(int index)
    {
        while (index > 0 && heap[index] > heap[(index - 1) / 2])
        {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void sift_down(int index)
    {
        int max_index = index;
        int left_child_index = index * 2 + 1;
        if (left_child_index < heap.size() && heap[left_child_index] > heap[max_index])
        {
            max_index = left_child_index;
        }
        int right_child_index = index * 2 + 2;
        if (right_child_index < heap.size() && heap[right_child_index] > heap[max_index])
        {
            max_index = right_child_index;
        }
        if (index != max_index)
        {
            swap(heap[index], heap[max_index]);
            sift_down(max_index);
        }
    }

public:
    // for maxheap, the class will contain
    // 1. a vector to store the heap

    void make_heap()
    {
        for (int i = heap.size() / 2 - 1; i >= 0; i--)
        {
            sift_down(i);
        }
    }

    void push_heap(int value)
    {
        heap.push_back(value);
        sift_up(heap.size() - 1);
    }

    void pop_heap()
    {
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        sift_down(0);
    }

    int top()
    {
        return heap[0];
    }

    bool empty()
    {
        return heap.empty();
    }

    int size()
    {
        return heap.size();
    }
};

class MinHeap
{
private:
    vector<int> heap;
    void heapify(int index)
    {
    }

    void sift_up()
    {
    }

public:
    void make_heap()
    {
        for (int i = 0;)
        {
        }
    }
};

int main()
{
    class MaxHeap heapds;

    heapds.push_heap(10);
    heapds.push_heap(20);
    heapds.push_heap(30);
    cout << heapds.top() << endl;
    heapds.pop_heap();
    heapds.push_heap(50);
    cout << heapds.top() << endl;
}