#ifndef DYNAMIC_PROGRAMMING_TEST_H_INCLUDED
#define DYNAMIC_PROGRAMMING_TEST_H_INCLUDED
#include <iostream>
#include <vector>
#include "Dynamic_Programming.h"

using namespace std;

//1 斐波那契树
void fibTest() {
    int n = 10;
    int result = fib(n);
    cout << result << endl;
}

//3 使用最小花费爬楼梯
void minCostClimbingStairsTest() {
    vector<int> cost = {1,100,1,1,1,100,1,1,100,1};
    int result = minCostClimbingStairs(cost);
    cout << result << endl;
}

//4 不同路径
void uniquePathsTest() {
    int m = 7, n = 10;
    int result = uniquePaths(m, n);
    cout << result << endl;
}

//5 不同路径2
void uniquePathsWithObstaclesTest() {
    vector<vector<int>> Obstical = {
        {0,0,0},{0,1,0},{0,0,0}
    };
    vector<vector<int>> Obstical2 = {{0,0}, {0,1}};
    int result = uniquePathsWithObstacles(Obstical2);
    cout << result << endl;
}

//6 整数拆分
void integerBreakTest() {
    int n = 5;
    int result = integerBreak(n);
    cout << result << endl;
}

//7 不同的二叉搜索树
void numTreesTest() {
    int n = 3;
    int result = numTrees(n);
    cout << result << endl;
}
#endif // DYNAMIC_PROGRAMMING_TEST_H_INCLUDED