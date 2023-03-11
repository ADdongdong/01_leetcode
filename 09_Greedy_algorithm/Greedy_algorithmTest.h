#ifndef GREEDY_ALGORITHMTEST_H_INCLUDED
#define GREEDY_ALGORITHMTEST_H_INCLUDED
#include <iostream>
#include "Greedy_algorithm.h"


using namespace std;

//1 分发饼干
void findContentChildrenTest() {
    vector<int> g = {1,2,3};
    vector<int> s = {1,1};
    int result = findContentChildren(g, s);
    cout << result << endl;
}



#endif // GREEDY_ALGORITHMTEST_H_INCLUDED
