#ifndef BACKTRACKINGTEST_H_INCLUDED
#define BACKTRACKINGTEST_H_INCLUDED
#include <iostream>
#include "Backtracking.h"

using namespace std;

//定义打印数组的函数
void printVector(vector<int> result){
    for (auto i:result) {
        cout << i<< endl;
    }
}

//定义打印二维数组的函数
void print2Vector(vector<vector<int>> result) {
    for (vector<int> i : result) {
        cout << "[";
        cout << i[0];
        for (int j = 1; j < i.size(); j++) {
            cout << ","<< i[j];
        }
        cout << "]" << ' ';
    }
    cout << endl;
}

//打印二维字符串数组
void print2VectorStr(vector<string> result) {
    for (string i : result) {
        cout << "[";
        cout << i[0];
        for (int j = 1; j < i.size(); j++) {
            cout << ","<< i[j];
        }
        cout << "]" << ' ';
    }
    cout << endl;
}

//1 生成组合测试
void backtrackCombinationTest() {
    backtrackCombination(4,2,1);
    print2Vector(result_01);
}

//2 组合综合(三)
void combinationSum3Test() {
    combinationSum3(5, 2, 0, 1);
    print2Vector(result_02);
}

//3 电话号码字母的组合测试
void letterCombinationsTest() {
    string dig = "23";
    letterCombinations(dig, 0);
    print2VectorStr(result_03);

}


#endif // BACKTRACKINGTEST_H_INCLUDED
