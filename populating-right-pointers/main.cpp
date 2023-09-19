#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// problem link : https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    Node *connect(Node *root)
    {
        queue<Node *> qt;

        qt.push(root);
        vector<Node *> nodes;

        while (!qt.empty())
        {
            Node *current = qt.front();
            qt.pop();
            nodes.push_back(current);
            std::cout << current->val << " " << endl;

            if (current->left != nullptr)
            {
                qt.push(current->left);
            }

            if (current->right != nullptr)
            {
                qt.push(current->right);
            }
        }

        int assignNullptr = 0;
        int count = 0;
        for (auto i = nodes.begin(); i != nodes.end(); i++)
        {
            auto current = *i;
            if (count == assignNullptr)
            {
                current->next = nullptr;
                assignNullptr == 0 ? assignNullptr = 2 : assignNullptr = assignNullptr * 2 + count;
            }
            else
                current->next = *(i + 1);

            count++;
        }

        return root;
    }
};

int main()
{
    Node *root = new Node(1);
    Node *c1 = new Node(2);
    Node *c2 = new Node(3);
    Node *c3 = new Node(4);
    Node *c4 = new Node(5);
    Node *c5 = new Node(6);
    Node *c6 = new Node(7);

    root->left = c1;
    root->right = c2;
    c1->left = c3;
    c1->right = c4;
    c2->left = c5;
    c2->right = c6;

    Solution s;
    s.connect(root);

    cout << c1->next->val << endl;
}