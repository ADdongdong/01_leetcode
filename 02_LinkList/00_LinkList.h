#ifndef _LINKLIST_H_INCLUDED
#define _LINKLIST_H_INCLUDED
#include <iostream>
using namespace std;

//简单定义链表
class LinkList{
public:
    //定义链表结点
    class ListNode{
    public:
        int val;
        ListNode* next;
        ListNode(int val):val(val), next(NULL){}
    };
    //构造函数
    LinkList(){
        m_dummyHead = new ListNode(0);
        m_size = 0;//虚拟头结点不会算入链表元素个数中，只为了操作方便
    }

    //1.获取链表中第index个节点的值，无效返回-1
    int get(int index);

    //2.在链表第一个元素之前添加一个值为val的节点作为新的头结点
    void addAtHead(int val);

    //3.将值为val的结点追加到链表的最后一个元素
    void addAtTail(int val);

    //4.在链表中的第index个节点之前添加值为val的节点，
    //若index等于链表长度，则将该结点添加到链表末尾，如果大于index,不会插入该结点
    //若index小于0，则在头部插入节点
    void addAtIndex(int index, int val);

    //5.删除链表指定index的结点
    void deleteAtIndex(int index);

    //6.移除链表指定元素
    void removeElements(int val);

    //7.链表翻转(翻转双指针)
    LinkList* reverseList();//返回一个新链表的指针

    //8.两两交换链表中的节点
    LinkList* swapPairs();

    //打印链表
    void PrintLinkList(){
        ListNode* cur = m_dummyHead;
        while (cur->next != NULL){
            cout<< cur->next->val << ' ';
            cur = cur->next;
        }
        cout << endl;
    }

private:
    int m_size;//记录链表中节点个数
    ListNode* m_dummyHead;//虚拟头结点
};


//1.获取链表中第index个节点的值，无效返回-1
int LinkList::get(int index){
    if(index > (m_size - 1) || index < 0){
        return -1;//检测输入index是否合规
    }
    ListNode* cur  = m_dummyHead->next;//让cur指向链表真正的第一个结点
    while(index--){
        cur = cur->next;
        //一会在这里做一个cout检测一下
    }
    return cur->val;//返回最终的结果
}

//2.在链表第一个元素之前添加一个值为val的节点作为新的头结点
void LinkList::addAtHead(int val){
    ListNode* newNode = new ListNode(val);
    newNode->next = m_dummyHead->next;
    m_dummyHead->next = newNode;
    m_size++;
}

//3.将值为val的结点追加到链表的最后一个元素
void LinkList:: addAtTail(int val){
    //先创建新结点
    ListNode* newNode = new ListNode(val);
    ListNode* cur = m_dummyHead;//为什么要让cur指向m_dummyHead呢？
    //因为，无论对于真正的头结点还是其他结点都可以一视同仁
    //比如此时链表为空，我们就可以直接使用这个函数来添加头结点
    //添加头结点和添加别的结点代码是一样的
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = newNode;
    m_size++;
}

//4.在链表中的第index个节点之前添加值为val的节点，
//若index等于链表长度，则将该结点添加到链表末尾，如果大于链表长度,不会插入该结点
//若index小于0，则在头部插入节点
void LinkList::addAtIndex(int index, int val){
    if(index > m_size){
        return;//大于链表长度，不会插入结点
    }
    if(index < 0){
        index = 0;//当成插入头结点
    }
    //使用虚拟结点，都可以一视同仁
//    if(index < 0){
//        this->addAtHead(val);//添加头结点
//    }
//    if(index == m_size){
//        this->addAtTail(val);//添加到尾结点
//    }
    //创建新结点
    ListNode* newNode = new ListNode(val);
    ListNode* cur = m_dummyHead;
    while(index--){
        cur = cur->next;//找到目标位置
    }
    //插入结点
    ListNode* temp = cur->next;
    cur->next = newNode;
    newNode->next = temp;
    m_size++;
}

//5.删除链表指定index的结点
void LinkList::deleteAtIndex(int index){
    if(index > m_size){
        return;
    }
    ListNode* cur = m_dummyHead;
    while (index--){
        cur = cur->next;
    }
    ListNode* temp = cur->next;//保存要删除的结点
    cur->next = cur->next->next;
    delete temp;
    m_size--;
}


//6.移除链表元素
void LinkList::removeElements(int val){
    //使用虚拟头结点重写
    ListNode* cur = m_dummyHead;
    while(cur->next != NULL){
        if(cur->next->val == val){
            ListNode* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
        }else{
            cur = cur->next;
        }
    }
}

//7.链表翻转(翻转双指针)
LinkList* LinkList::reverseList(){
    ListNode* temp;//保存cur的下一个结点
    ListNode* cur = m_dummyHead->next;
    ListNode* pre = NULL;
    while(cur){
        temp = cur->next;//保存下一个结点
        cur -> next = pre;//next指向前一个指针
        pre = cur;//pre指针前进一个结点
        cur = temp;//cur指针前进一个结点
    }
    LinkList* reverse_list = new LinkList();//定义虚拟头结点
    reverse_list->m_dummyHead->next = pre;
    return reverse_list;
}

//8.两两交换链表中的节点
LinkList* LinkList::swapPairs(){
//思路
//n->1->2->3->4
//n->2,2->1,1->3
//效果，就好像把一个弯曲的绳子拉直了一样
//经过这三步的操作，可以把当前结点后面的两个结点顺序颠倒
//这时候，只要让cur= cur->next->next，然后再进行这三步操作
//就可以把后面连续的两个结点顺序颠倒了
    ListNode* cur = m_dummyHead;
    while(cur->next != NULL && cur->next->next != NULL){
        //我们要把cur结点后面的两个结点顺序颠倒
        //所以，就要判断cur结点的后面两个结点时候是空
        //若都不是空才可以颠倒，若有一个是空，就没法颠倒了

        ListNode* temp = cur->next;//记录临时结点
        //temp是要颠倒的两个结点中的第一个结点
        ListNode* temp1 = cur->next->next->next;
        //temp1是下次要颠倒的两个结点中的第一个结点
        //进行三部
        cur->next = cur->next->next;
        cur->next->next = temp;
        cur->next->next->next = temp1;

        cur = cur->next->next;
    }
    LinkList* rl = new LinkList();
    rl->m_dummyHead = m_dummyHead;
    return rl;
}
#endif // 00_LINKLIST_H_INCLUDED
