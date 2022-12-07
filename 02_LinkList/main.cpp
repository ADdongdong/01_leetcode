#include <iostream>
#include "00_LinkList.h"

using namespace std;

int main()
{
    LinkList* l1 = new LinkList;
    LinkList* l2 = new LinkList;

    l1->addAtTail(1);
    l1->addAtTail(2);
    l1->addAtTail(3);
    l1->addAtTail(4);
    l1->addAtTail(5);

    l2->addAtTail(9);
    l2->addAtTail(8);

    ListNode* head1 = l1->getHead();
    ListNode* head2 = l2->getHead();
    head2->next->next = head1->next->next;

    ListNode* inter = l1->getIntersectionNode(l2);
    l2->PrintLinkList();
    l1->PrintLinkList();
    cout << inter->val << endl;//成功啦


    return 0;
}
