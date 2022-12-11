#ifndef _HASHTABLETEST_H_INCLUDED
#define _HASHTABLETEST_H_INCLUDED
#include <iostream>
#include <vector>
#include <unordered_set>
#include "00_HashTable.h"
using namespace std;

template<class T>void PrintVector(vector<T> v1);

//1.isAnagnamTest()
void isAnagnamTest(){
    string s = "cat";
    string t = "atd";
    bool result = isAnagram(s, t);
    cout <<"结果是：" <<result << endl;
}

//2.intersectionTest()
void intersectionTest(){
    vector<int> nums1 = {1,2,3,4,5,6,5,6,7,8};
    vector<int> nums2 = {2,3,4,9,19,12};
    vector<int> result;
    result = intersection(nums1, nums2);
    PrintVector<int>(result);

}

//3.isHappyTest()
void isHappyTest(){
    int n;
    cout << "请输入要检测的数字：" ;
    cin >> n;
    cout << isHappy(n) << endl;

}

//4.twoSumTest()
void twoSumTest(){
    vector<int> nums = {1,2,3,4,5};
    vector<int> result = twoSum(nums, 5);
    PrintVector(result);
}

//5.fourSumCountTest()
void fourSumCountTest(){
    vector<int> A = {1,2};
    vector<int> B = {-2,1};
    vector<int> C = {-1,2};
    vector<int> D = {0,2};
    int result = 0;
    result = fourSumCount(A, B, C, D);
    cout << result << endl;
}



//定义打印vector的函数模板
template<class T>
void PrintVector(vector<T> v){
    //gcc编译器无法识别vector<T>::iterator是一个类型
    //所以，前面要加上typename/class来说明这是一个类型
    typedef class/*class*/ vector<T>::iterator IT;
    for(IT it = v.begin(); it != v.end(); it++){
        cout << *it << ' ';
    }
    cout << endl;
}


#endif // 01_HASHTABLETEST_H_INCLUDED
