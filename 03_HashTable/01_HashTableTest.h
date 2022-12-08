#ifndef _HASHTABLETEST_H_INCLUDED
#define _HASHTABLETEST_H_INCLUDED
#include <iostream>
#include "00_HashTable.h"
using namespace std;

//1.isAnagnamTest()
void isAnagnamTest(){
    string s = "cat";
    string t = "atd";
    bool result = isAnagram(s, t);
    cout <<"结果是：" <<result << endl;
}


#endif // 01_HASHTABLETEST_H_INCLUDED
