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

//1 生成组合测试
void backtrackCombinationTest() {
    backtrackCombination(4,2,1);
    print2Vector(result_01);
}



#endif // BACKTRACKINGTEST_H_INCLUDED
