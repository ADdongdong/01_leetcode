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

    LinkList* l2 = l1->swapPairs();
    l2->PrintLinkList();//测试成功

    return 0;
}
