#include <iostream>

using namespace std;

class BST
{
public:
    int val;
    BST *left;
    BST *right;
    BST(int data)
    {
        val = data;
        left = nullptr;
        right = nullptr;
    }

    void printNode()
    {
        cout << val << endl;
    }
};

int main()
{
    BST *root = new BST(5);
    root->printNode();
}