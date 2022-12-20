#ifndef _DOOUBEEPOINTER_H_INCLUDED
#define _DOOUBEEPOINTER_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;

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

#endif // 00_DOOUBEEPOINTER_H_INCLUDED
