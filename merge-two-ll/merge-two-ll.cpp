#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
};

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{

    if (list1 == nullptr && list2 != nullptr)
    {
        return list2;
    }
    else if (list1 != nullptr && list2 == nullptr)
    {
        return list1;
    }
    else if (list1 == nullptr && list2 == nullptr)
    {
        return nullptr;
    }

    ListNode *currList1 = list1;
    ListNode *currList2 = list2;
    ListNode *prev = nullptr;

    while (currList1 != nullptr && currList2 != nullptr)
    {
        // if(currLis)
        if (currList1->val <= currList2->val)
        {
            if (currList1->next == nullptr)
            {
                prev = currList1;
            }
            currList1 = currList1->next;
        }
        else if (currList2->val < currList1->val)
        {

            ListNode *temp = new ListNode;
            temp->val = currList1->val;
            temp->next = currList1->next;
            currList1->val = currList2->val;
            currList1->next = temp;
            if (currList2->next == nullptr)
            {
                prev = currList2;
            }
            currList2 = currList2->next;
        }
    }

    if (currList1)
    {
        prev->next = currList1;
    }
    if (currList2)
    {
        prev->next = currList2;
    }

    return list1;
}

int main()
{
    ListNode *n1 = new ListNode;
    ListNode *n2 = new ListNode;
    ListNode *n3 = new ListNode;
    ListNode *n4 = new ListNode;
    ListNode *n5 = new ListNode;
    ListNode *n6 = new ListNode;
    n1->val = 1;
    n1->next = n2;

    n2->val = 2;
    n2->next = n3;

    n3->val = 3;
    n3->next = nullptr;

    n4->val = 1;
    n4->next = n5;

    n5->val = 3;
    n5->next = n6;

    n6->val = 5;
    n6->next = nullptr;

    mergeTwoLists(n1, n4);
}