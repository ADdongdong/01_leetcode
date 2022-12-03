#include <iostream>
#include "00_LinkList.h"

using namespace std;

int main()
{
    LinkList* l1 = new LinkList;
    l1->addAtTail(1);
    l1->addAtTail(2);
    l1->addAtTail(3);
    l1->addAtTail(4);
    l1->addAtTail(5);

    l1->addAtHead(10);
    l1->deleteAtIndex(3);
    l1->removeElements(5);
    l1->addAtIndex(3,50);
    l1->PrinLinkList();

    LinkList* rl = l1->reverseList();
    rl->PrinLinkList();


    return 0;
}
