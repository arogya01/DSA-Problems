#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//swapping nodes in ll... 
class Solution
{
public:
    ListNode *swapNodes(ListNode *head, int k)
    {

        ListNode *swapNodeOne;
        ListNode *swapNodeTwo;
        ListNode *iter = head;
        ListNode *prev;
        int count = 0;
        while (iter)
        {
            if (count == k)
            {
                swapNodeOne = iter;
            }
            count++;
            iter = iter->next;
        }

        cout << "the size of linked list is" << count;

        int endCount = count - k;
        iter = head;
        int k2 = 0;
        while (iter)
        {
            if (k == endCount)
            {
                swapNodeTwo = iter;
                break;
            }
            k2++;
            iter = iter->next;
        }

        cout << swapNodeOne->val << endl;
        cout << swapNodeTwo->val << endl;

        return head;
    }
};

int main()
{
    ListNode *l5 = {5};
    ListNode *l4(4, l5);
    ListNode *l3(3, l4);
    ListNode *l2(2, l3);
    ListNode *l1(1, l2);

    Solution s;
    s.swapNodes(l1, 2);
}