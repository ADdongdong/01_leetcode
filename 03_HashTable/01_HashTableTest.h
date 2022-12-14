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

//6.canConstructTest()
void canConstructTest(){
    string s1 = "aabbccdef";
    string s2 = "aaabbbcccddef";
    string s3 = "abc";
    bool result1 = canConstruct(s1, s2);
    bool result2 = canConstruct(s1, s3);
    cout << result1 << endl;
    cout << result2 << endl;

}

//7.threeSumTest()
void threeSumTest(){
    vector<int> nums = {-1,0,1,2,-1,4};
    vector<int> nums2 = {-1, -1, 2};
    vector<vector<int>> result = threeSum(nums2);
    PrintDim2Vector(result);
}

//8.fourSumTest()
void fourSumTest(){
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;
    vector<vector<int>> result = fourSum(nums, target);
    PrintDim2Vector(result);
}

#endif // 01_HASHTABLETEST_H_INCLUDED
