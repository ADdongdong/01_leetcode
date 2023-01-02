#ifndef BITREETEST_H_INCLUDED
#define BITREETEST_H_INCLUDED
#include <iostream>
#include <vector>
#include "biTree.h"

using namespace std;

void pre_traversal_test() {
    TreeNode<int>* T;
    cout << "请按照先序顺序创建二叉树" << endl;
    create<int>(&T);
    cout << "对T进行先序遍历" <<endl;
    vector<int> result;
    pre_traversal<int>(T, result);
    for (int i:result) {
        cout << i << ' ';
    }
    cout << endl;
}


#endif // BITREETEST_H_INCLUDED
