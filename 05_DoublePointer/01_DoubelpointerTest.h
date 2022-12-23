#ifndef _DOUBELPOINTERTEST_H_INCLUDED
#define _DOUBELPOINTERTEST_H_INCLUDED
#include "00_DooubeePointer.h"
#include <iostream>
using namespace std;

//1.removeElementTest
void removeElementTest(){
    vector<int> nums = {1,2,3,3,4,5};
    int result = removeElement(nums, 3);
    cout << result << endl;
}

//2.ReverseListTest
void reverseListTest(){
    ListNode* L = new ListNode(0);
    ListNode* l1 = new ListNode(1);
    ListNode* l2 = new ListNode(2);
    ListNode* l3 = new ListNode(3);
    l2->next = l3;
    l1->next = l2;
    L->next = l1;

    ListNode* temp = L;
    while (temp) {
        cout << temp->val << ' ';
        temp = temp -> next;
    }
    cout << endl;

    ListNode* result = reverseList(L);
    ListNode* temp1 = result;
    while (temp1) {
        cout << temp1->val << ' ';
        temp1 = temp1 -> next;
    }
    cout << endl;
}
#endif // 01_DOUBELPOINTERTEST_H_INCLUDED
