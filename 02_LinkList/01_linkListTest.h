#ifndef _LINKLISTTEST_H_INCLUDED
#define _LINKLISTTEST_H_INCLUDED
#include <iostream>
#include "00_LinkList.h"

//创建一个的链表,输入num输出一个1->num个结点的有序链表
LinkList* sequence(int num){
    LinkList* l1 = new LinkList;
    int m_num = 1;
    while(m_num <= num){
        l1->addAtTail(m_num);
        m_num++;
    }

    return l1;
}

//链表算法11的测试代码
void test_11(){
    LinkList* l1 = sequence(7);
    ListNode* head = l1->getHead();
    ListNode* tail = l1->getTail();

    tail->next = head->next->next;//构造一个环
    cout << tail->next->val << endl;

    ListNode* cycle = l1->detectCycle();//寻找入环结点，让指针cycle指向这个结点
    cout << cycle->val << endl;//成功找到
}




#endif // 01_LINKLISTTEST_H_INCLUDED
