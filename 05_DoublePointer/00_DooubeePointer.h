#ifndef _DOOUBEEPOINTER_H_INCLUDED
#define _DOOUBEEPOINTER_H_INCLUDED
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
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
ListNode* removeNthFromEnd(ListNode* head, int n){
//倒数第n个结点，是正数第几个结点？
//假设共N个结点，是正数第N-n个结点
//先让fast指向第n个结点，那么就剩下了N-n个结点
//此时让slow指向第一个结点，然后,fast和slow同时移动
//当fast移动到末尾时候，slow停止，fast走过了N-n个结点，slow也走到了第N-n个结点
//即就是倒数第n个结点，删除就行le
    //定义虚拟头结点
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* fast = dummy;
    ListNode* slow = dummy;
    while (n-- && fast != NULL){
        fast = fast->next;
    }
    fast = fast->next;
    while (fast){
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;
    return dummy->next;
}

//7.链表相交
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//链表相交的特点，如果在第n个结点相交，则后面的结点都是共同结点
//双指针可以是查找效率最高
//一个特点：公共的结点数量一定小于等于min(len(a),len(b))
//所以，找到最短的链表，然后，锻炼表从头开始遍历，长链表从倒数第len(short)个结点开始遍历查找
    ListNode* curL;
    ListNode* curS;
    curL = headA;
    curS = headB;
    int lenL = 0, lenS = 0;
    while (curL) {
        curL= curL->next;
        lenL++;
    }
    while (curS) {
        curS= curS->next;
        lenS++;
    }

    curL = headA;
    curS = headB;
    if(lenS > lenL) {
        //交换
        swap(lenL, lenS);
        swap(curL, curS);
    }

    //找到长链表的倒数第lenS个结点
    int n = lenL - lenS;
    while (n-- && curL != NULL){
        curL = curL->next;
    }

    while (curL != NULL) {
        if (curL == curS) {
            return curL;
        }else {
            curL = curL->next;
            curS = curS->next;
        }
    }
    return NULL;
}

//8.环形链表
ListNode *detectCycle(ListNode *head) {
//1.如何判断有环
//slow一次走一个结点，fast一次走2个结点，
//当slow和fast相遇的时候，就说明有环
//2.如何找到环入口
//相遇的时候，一个指针指向相遇结点，一个执行头结点，同时移动，每次都移动一个单位
//当两个指针相遇，就找到的环的入口
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            //如果slow和fast指向同一个结点的说明就有环了
            if (slow == fast) {
                ListNode* index1 = slow;
                ListNode* index2 = head;
                while (index1 != index1) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index1;//找到入口结点了
            }
        }
        return NULL;
}

//9.三数字之和
vector<vector<int>> threeSum(vector<int>& nums) {
    //定义二维数组
    vector<vector<int>> result;
    //先对nums进行排序
    sort(nums.begin(), nums.end());
    //遍历列表
    for (int i = 0; i < nums.size(); i++) {
        //对每一个i进行判断，看是不是大于0
        if (nums[i] > 0) {
            break;
        }

        //对当前的i进行去重复
        if (i > 0 && nums[i] == nums[i-1]) {
            continue;
        }

        //定义left和right
        int left = i;
        int right = nums.size();
        while (left < right) {
            //有三种情况
            if (left < right && nums[i] + nums[left] + nums[right] > 0) right--;
            else if(left < right && nums[i] + nums[left] + nums[right] < 0) left++;
            else {
                //先将这一组值加入到result中
                result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                //去重
                while (left < right && nums[left] == nums[left+1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;

                //left和right进行相向移动
                left++;
                right--;
            }
        }
    }
    return result;
}

//10.四数字之和
vector<vector<int>> fourSum(vector<int>& nums, int target) {
//和三数之和思路基本相同，但有个区别，就是
//判断break的时候，负数相加会变成更小的负数，所以，
//要给break的判断条件加上nums[i] > 0
    vector<vector<int>> result;
    //排序
    sort(nums.begin(), nums.end());
    //for循环进行遍历
    for (int i = 0; i < nums.size(); i++) {
        //判断break
        if (nums[i] > target && nums[i] > 0) {
            break;
        }

        //去重
        if (i > 0 && nums[i] == nums[i-1]) {
            continue;
        }
        //进行第二个数字的for循环
        for (int j = i + 1; j < nums.size(); j++){
            //判断break,做这个判断的目的是为了减少运算量，加快运算速度
            if (nums[i] + nums[j] > target && nums[i] + nums[j] > 0) {
                break;
            }

            //去重
            if (j > i+1 && nums[j] == nums[j-1]) {
                continue;
            }

            //定义当前i的当前j下的left和right
            int left = j + 1, right = nums.size() - 1;
            //寻找当前i和当期那j下满足条件的left和right
            while (left < right) {
                //有三种情况
                if ((long)nums[i] + nums[j] + nums[left] + nums[right] > target) right--;
                else if ((long)nums[i] + nums[j] + nums[left] + nums[right] < target) left--;
                else {
                    //先将这个数组添加到result中
                    result.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                    //去重
                    while (left < right && nums[right] == nums[right-1]) right--;
                    while (left < right && nums[left] == nums[left+1]) left++;

                    //left和right相向移动
                    left++;
                    right--;
                }
            }
        }
    }
    return result;
}
#endif // 00_DOOUBEEPOINTER_H_INCLUDED
