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
    cout << "[";
    //for (vector<int> i : result) {
    for (int i = 0; i < result.size(); i++){
        //如果遇到了空数组，就对其进行特殊处理，不然程序会终止
        if (result[i].size() == 0) {
            cout << "[]";
            continue;
        }
        if (i == 0) {
            cout << "[";
            cout << result[0][0];
            for (int j = 1 ; j < result[0].size(); j++){
                cout << ","<< result[0][j];
            }
            cout << "]";
            continue;
        }

        cout << ", [";
        cout << result[i][0];
        for (int j = 1; j < result[i].size(); j++) {
            cout << ","<< result[i][j];
        }
        cout << "]";
    }
    cout << "]" << endl;
}

//打印二维字符串数组
void print2VectorStr(vector<string> result) {
    for (string i : result) {
        cout << "[";
        cout << i[0];
        for (int j = 1; j < i.size(); j++) {
            cout << ","<< i[j];
        }
        cout << "]" << endl;
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

//7 测试复原IP地址
void restoreIpAddressesTest() {
    string s = "25525511135";
    restoreIpAddresses(s, 0, 0);
    for(auto i : result_07) {
        cout << i << endl;
    }
}

//8 子集测试
void subsetsTest() {
    vector<int> nums = {1, 2, 3};
    subsets(nums, 0);
    print2Vector(result_08);
}

//9 子集2测试
void subsets2Test() {
    vector<int> nums = {1, 2, 2};
    vector<bool> used(nums.size(), false);
    sort(nums.begin(), nums.end());
    subsets2(nums, used, 0);
    print2Vector(result_09);
}

//10 递增子序列
void findSubsequencesTest() {
    vector<int> nums = {4, 4, 3, 2, 1};
    findSubsequences(nums, 0);
    print2Vector(result_10);
}

//11 全排列
void permuteTest() {
    vector<int> nums = {1, 2, 3};
    vector<bool> used(nums.size(), false);
    permute(nums, used, 0);
    print2Vector(result_11);
}

//11 全排列
void permuteUniqueTest() {
    vector<int> nums = {1, 1, 3};
    vector<bool> used(nums.size(), false);
    sort(nums.begin(), nums.end());
    permuteUnique(nums, used, 0);
    print2Vector(result_12);
}

//13 N皇后
void solveNQueensTest() {
    int n = 4;
    //创建一个空棋盘，这个空气盘有四行，每一行都有四个.代表4个没有放置棋子的位置
    vector<string> chessboard(n, string(n, '.'));
    solveNQueens(n, 0, chessboard);
    //注意，result_13是vector<vector<string>>类型
    for(auto i : result_13) {
        print2VectorStr(i);
    }
}
#endif // BACKTRACKINGTEST_H_INCLUDED
