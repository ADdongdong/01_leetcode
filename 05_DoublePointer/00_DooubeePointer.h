#ifndef _DOOUBEEPOINTER_H_INCLUDED
#define _DOOUBEEPOINTER_H_INCLUDED
#include <iostream>
#include <vector>
#include <list>
using namespace std;

/*双指针用法一：使用原数组经过某种规则生成新数组
 *所谓的双指针，其实就是两个指针分别指向不同的数组
 *或者说是，一个数组，和这个数组经过某种处理后生成的另一个数组
 *一个指针指向旧数组，一个指针指向新数组。
 *一般来说，指向旧数组的就是fast指针，因为要根据旧数组的情况来决定新数组对应位置的元素
 *所以，肯定会先检测旧数组
 *一般来说，指向新数组的就是slow指针，因为逻辑的先后关系，新数组的生成总慢就数组的处理一步
 *所以，指向新数组的必然是slow指针。
 *
 *同时，一般情况下，我们要求的数组，就是slow数组了。

 *双指针用法二：只用一轮循环反转数组
 */

//1.移除元素
int removeElement(vector<int>& nums, int val){
//描述：
//给定一个数组nums和一个值val,原地地移除所有数值等于val对的元素
//并且返回移除后数组新的长度
//思路:
//双指针，fast和slow
//fast指向原来的nums的元素，slow指向移动后新元素的末尾，
//如果检测到nums[fast] != val,那么fast给slow赋值(也就是无视val,让非val的元素按顺序占了val的位置就行)
//并且fast++,slow++
//最后修改只需要将nums.size(slow + 1)就可以了
    int slow = 0;
    for(int fast = 0; fast < nums.size(); fast++){
        if (val != nums[fast]) {
            nums[slow++] = nums[fast];
        }
    }
    return slow;//这里为什么返回slow，而不是slow+1,因为if里面是nums[slow++]
    //也就是说，最后一个不是val的值移动完了以后，slow还会再往前走一步，这就是最终nums的size了
}

//2.翻转字符串
void reverseString(vector<char>& nums){
    for (int i = 0, j = nums.size()-1; i < nums.size()/2; i++, j--) {
        swap(nums[i], nums[j]);
    }
}

//3.替换空格
string replaceSpace(string s){
    //保存原始字符串的长度
    int oldSize = s.size();
    //计算添加%20以后字符串的长度
    int _count = 0;
    for (auto i : s) {
        if (i == ' ') {
            //如果遇到一个空格，就增加两个字符的长度，
            //%20虽然是3个字符，但是，原来的空格也算是一个字符
            _count += 2;
        }
    }
    //修改串长度
    s.resize(s.size() + _count);
    //记录新字符串的长度
    int newSize = s.size();
    //使用双指针法进行替换
    //从后往前替换，这样会尽可能减少元素的移动
    for (int i = oldSize - 1, j = newSize - 1; i < j; i--, j--) {
        //i指向原来字符串的最后一个元素
        //j指向新字符串的最后一个位置
        //移动规则，如果不是空格，则直接i位置元素移动到j
        //如果是空格，则j从后往前添加0,2,%,并且，j要往前移动两个单位
        if (s[i] != ' '){
            s[j] = s[i];
        }else{
            s[j] = '0';
            s[j-1] = '2';
            s[j-2] = '%';
            j -= 2;//目前j指向'0',再往前移动两个指向了'%',for还会再往前移动一个单位
        }
    }
    return s;
}

//4.翻转字符串里的单词
void removeExtraSpace(string& s){
//首先移除多余的空格
//双指针法，只对非空格的元素进行操作，
    //slow指向移动只有元素的末尾位置
    //i是fast指针，指向原来元素的末尾位置
    int slow = 0;
    for (int i = 0; i < s.size(); i++){
        if (s[i] != ' '){
        //只对非空格的元素进行操作
            //在每个单词后面添加一个空格
            //如果slow是第一个单词的第一个元素，且不是空格，这时候不加空格
            if (slow != 0) {s[slow++] = ' ';}
            //移动单词的位置
            while (i < s.size() && s[i] != ' ') {
                    s[slow++] = s[i++];
            }
        }
    }
    s.resize(slow);
}

void reverseStringPlus(string& s, int _begin, int _end ){
    for (int i = _begin, j = _end-1; i < j; i++, j--){
        swap(s[i], s[j]);
    }
}

string reverseWords(string s){
    //删除多余的空格
    removeExtraSpace(s);
    //整个字符串整体翻转
    reverseStringPlus(s, 0, s.size());
    //对里面的每一个单词分别进行翻转,还是使用双指针
    int _begin = 0;//first
    for (int i = 0; i < s.size(); i++) {
        //什么时候进行翻转呢
        if (i == s.size() || s[i] == ' '){
            reverseStringPlus(s, _begin, i);
            _begin = i+1;//更新头指针的位置
        }
    }
    return s;
}

//5.翻转链表
class ListNode{
public:
    int val;
    ListNode *next;
    ListNode(int x) :val(x), next(NULL){}
};

ListNode* reverseList(ListNode* l){
//双指针法，就这里就不使用虚拟头结点了，因为翻转过来以后，第一个结点的next是要指向NULL的
    //ListNode* pre = l;
    //ListNode* cur = l->next;//如果这个链表为空，则会报错
    //处理头结点
    //pre->next = NULL;
    ListNode* temp;
    ListNode* pre = NULL;
    ListNode* cur = l;
    while(cur != NULL) {
        ListNode* temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    ListNode* newList = pre;
    return pre;
}

//6.删除链表的倒数第n个结点

#endif // 00_DOOUBEEPOINTER_H_INCLUDED
