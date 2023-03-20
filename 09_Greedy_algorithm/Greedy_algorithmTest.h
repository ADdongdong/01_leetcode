#ifndef GREEDY_ALGORITHMTEST_H_INCLUDED
#define GREEDY_ALGORITHMTEST_H_INCLUDED
#include <iostream>
#include <vector>
#include "Greedy_algorithm.h"


using namespace std;

//1 分发饼干
void findContentChildrenTest() {
    vector<int> g = {1,2,3};
    vector<int> s = {1,1};
    int result = findContentChildren(g, s);
    cout << result << endl;
}

//2 摆动序列
void wiggleMaxLengthTest() {
    vector<int> nums = {1, 7, 4, 9, 2, 5};
    int result = wiggleMaxLength(nums);
    cout << result << endl;
}

//3 最大子序列和
void maxSubArrayTest() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    int result = maxSubArray(nums);
    cout << result << endl;
}

//9 分发糖果
void candyTest() {
    vector<int> nums = {1,0,2};
    int result = candy(nums);
    cout << result << endl;
}

//10 柠檬水找零
void lemonadeChangeTest() {
    vector<int> bills = {5,5,5,10,20};
    bool result = lemonadeChange(bills);
    cout << result << endl;
}

//11 使用最少数量的箭引爆气球
void findMinArrowShotsTest() {
    vector<vector<int>> points = {{1,2}, {3,4}, {5,6}, {7,8}};
    int result = findMinArrowShots(points);
    cout << result << endl;

}

//13 无重叠区间
void eraseOverlapIntervalsTest() {
    //[ [1,2], [2,3], [3,4], [1,3] ]
    vector<vector<int>> intervals = {{1,2}, {2,3}, {3, 4}, {1,3}};
    int result = eraseOverlapIntervals(intervals);
    cout << result << endl;
}

void MergeTest(){
    /*输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
     *输出：[[1,6],[8,10],[15,18]]
     */
    //vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> intervals = {{1,3}};
    vector<vector<int>> result = Merge(intervals);
    print2Vector(result);
}
#endif // GREEDY_ALGORITHMTEST_H_INCLUDED
