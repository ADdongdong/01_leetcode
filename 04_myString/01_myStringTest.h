#ifndef _MYSTRINGTEST_H_INCLUDED
#define _MYSTRINGTEST_H_INCLUDED
#include "00_myString.h"
#include <iostream>
#include <vector>
using namespace std;

//1.翻转字符串
void reverseStringTest(){
    vector<char> s = {'a','b','c'};
    reverseString(s);
    PrintVector(s);
}

//2.翻转字符串2
void reverseStrIITest(){
    string s = "abcdefg";
    string result = reverseStrII(s,2);
    cout << result << endl;
}

//3.替换空格test
void replaceSpaceTest(){
    string s = "We are happy";
    string result = replaceSpace(s);
    cout << result << endl;
}

//4.翻转字符串测试
void reverseWordsTest(){
    string s = "hello world";
    string result = reverseWords(s);
    cout << result << endl;
}

//5.左旋转字符串测试
void leftMoveTest(){
    string s = "abcdefg";
    leftMove(s, 2);
    cout << s << endl;
}


//6.kmp算法test

//7.repeatedSubstringPatternTest

#endif // 01_MYSTRINGTEST_H_INCLUDED
