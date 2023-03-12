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

#endif // GREEDY_ALGORITHMTEST_H_INCLUDED
