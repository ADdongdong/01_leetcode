#ifndef BITREETEST_H_INCLUDED
#define BITREETEST_H_INCLUDED
#include <iostream>
#include <vector>
#include "biTree.h"

using namespace std;

//二叉树的遍历测试
void traversal_test() {
    TreeNode<int>* T;
    cout << "请按照先序顺序创建二叉树" << endl;
    create<int>(T);
    cout << "输出先序遍历顺序: " <<endl;
    vector<int> result;
    //测试先序遍历
    pre_traversal<int>(T, result);
    for (int i:result) {
        cout << i << ' ';
    }
    cout << endl;
    //测试中序遍历
    vector<int> result1 = in_Traversal(T);
    cout << "输出中序遍历顺序:" << endl;
    for (int i:result1) {
        cout << i << ' ';
    }
    cout << endl;
    //测试后序遍历
    vector<int> result2 = post_Traversal(T);
    cout << "输出后序遍历顺序:" << endl;
    for (int i:result2) {
        cout << i << ' ';
    }
    cout << endl;
    //层序遍历测试
    vector<vector<int>> result3;
    result3 = leave_Order(T);
    cout << "输出层序遍历顺序:" << endl;
    for (auto iterow = result3.begin(); iterow != result3.end(); iterow++){
        for (auto itcolumn = (*iterow).begin(); itcolumn != (*iterow).end(); itcolumn++) {
            cout <<  *itcolumn << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


#endif // BITREETEST_H_INCLUDED
