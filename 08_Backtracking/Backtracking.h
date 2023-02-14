#ifndef BACKTRACKING_H_INCLUDED
#define BACKTRACKING_H_INCLUDED
#include <iostream>
#include <vector>

using namespace std;

//1 组合问题
//定义result_01，用来储存最后的结构，这是一个二维数组，其中每一个元素都是一个一维数组
vector<vector<int>> result_01;
//定义path_01,这个数组中只维护k个元素，如果path_01中元素个数满足k个，就将当前path_01加入到result_01中
vector<int> path_01;
void backtrackCombination(int n, int k, int starIndex) {
    //1.1 返回值：无返回值，
    //1.2 参数，当前是找[1, n]中元素的组合，所以，要给出这个范围
    //    参数k，一个组合中要有几个元素
    //    参数starIndex 表示当前递归从哪里开始
    //2 递归终止的条件
    if (path_01.size() == k) {
        //如果当前path_01的长度已经满足的组合k的长度
        //那就将当前path_01加入到result_01中
        result_01.push_back(path_01);
        return;//返回上一层递归
    }
    //3.单层递归的逻辑
    for (int i = starIndex; i <= n; i++) {
        //单层遍历，从starIndex开始，到n结束，注意，这里是包括n的，所以要加上等于号
        path_01.push_back(i);//将这个元素加入到path_01中
        //继续进行递归遍历，往当前path_01中添加元素
        backtrackCombination(n, k, i + 1);//下次起始元素就是这个元素的下一个位置了
        //遍历完以后，要进行回溯
        path_01.pop_back();
    }
}



#endif // BACKTRACKING_H_INCLUDED
