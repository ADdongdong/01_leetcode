#ifndef _MYSTRING_H_INCLUDED
#define _MYSTRING_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//打印vector
template<class T>
void PrintVector(vector<T> v){
    for(auto a : v){
        cout << a << ' ';
    }
    cout << endl;
}

//1.翻转字符串
void reverseString(vector<char>& s){
//翻转字符串的本质就是翻转字符数组
    for(int i = 0; i < s.size()/2; i++){
        //两个指针指向的元素来回交换就行了
        char temp = s[i];
        s[i] = s[s.size()-1-i];
        s[s.size()-1-i] = temp;
    }
}

//2.翻转字符串II
string reverseStrII(string s, int k){
//描述
//给定一个字符串s和一个区间k
//丛s的开始到末尾，每次截取2k个元素，翻转前k个,后k个不变
//如果最后剩下的元素不足k个,则不翻转，如果剩下的元素超过k,则翻转前k个元素
//思路
//本来是for循环是i++,现在编程i += 2k,即每次向前走2k个，就直接到了下一个2k
//我们对这个2k做翻转就行了
    for (int i = 0; i < s.size(); i += (2*k)){
        //情况
        //1.i+k还在s内，则翻转i到i+k
        //2.i+2k已经超过了s的长度，i+k没有超过s长度，则翻转前i到i+k个
        if(i+k <= s.size()){
            reverse(s.begin() + i, s.begin() + i + k);//string 的reverse是包前不包后的，左闭右开
        } else {
            //3.剩余少于k个元素，全部翻转
            reverse(s.begin()+i, s.end());
        }
    }
    return s;
}

#endif // 00_MYSTRING_H_INCLUDED
