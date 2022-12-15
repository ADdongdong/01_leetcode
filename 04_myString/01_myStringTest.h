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
#endif // 01_MYSTRINGTEST_H_INCLUDED
