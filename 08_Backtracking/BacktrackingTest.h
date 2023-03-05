#ifndef BACKTRACKINGTEST_H_INCLUDED
#define BACKTRACKINGTEST_H_INCLUDED
#include <iostream>
#include <algorithm>
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

//4 测试数组总和
void combinationSumTest() {
    vector<int> candidates = {2, 3, 6, 7};
    combinationSum(0, 7, candidates, 0);
    print2Vector(result_04);
}

//5 数组总和2
void combinationSum2Test() {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    //定义used数组，类型为bool类型
    vector<bool> used(candidates.size(), false);//初试化这个数组，大小为candidates.size()，里面所有元素都为false
    sort(candidates.begin(), candidates.end());
    combinationSum2(8, 0, 0, candidates, used);
    print2Vector(result_05);
}

//6 分割回文串测试
void PartitionTest() {
    string s = "aab";
    Partition(s, 0);
    for (auto i : result_06){
        print2VectorStr(i);
    }
}
#endif // BACKTRACKINGTEST_H_INCLUDED
