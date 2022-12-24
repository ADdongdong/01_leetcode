#ifndef _DOUBELPOINTERTEST_H_INCLUDED
#define _DOUBELPOINTERTEST_H_INCLUDED
#include "00_DooubeePointer.h"
#include <iostream>
using namespace std;
//定义函数打印二维vector
void PrintVector2D(vector<vector<int>> nums){
    for (auto i : nums){
        for (int j = 0; j < i.size(); j++){
            cout << i[j] << ' ';
        }
        cout << endl;
    }
}


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

//3.删除倒数第n个结点测试
void removeNthFromEndTest(){
    ListNode* L = new ListNode(0);
    ListNode* l1 = new ListNode(1);
    ListNode* l2 = new ListNode(2);
    ListNode* l3 = new ListNode(3);
    l2->next = l3;
    l1->next = l2;
    L->next = l1;

    ListNode* result = removeNthFromEnd(L, 2);
    ListNode* temp1 = result;
    while (temp1) {
        cout << temp1->val << ' ';
        temp1 = temp1 -> next;
    }
    cout << endl;

}

//4.四个元素之和
void fourSumTest() {
    vector<int> nums = {1,0,-1,0,-2,2};
    vector<vector<int>> nums2 = {{-2,-1,1,2},{-2,0,0,2},{-1,0,0,1}};
    vector<vector<int>> result = fourSum(nums, 0);
    PrintVector2D(result);
}

#endif // 01_DOUBELPOINTERTEST_H_INCLUDED
