#ifndef BITREETEST_H_INCLUDED
#define BITREETEST_H_INCLUDED
#include <iostream>
#include <vector>
#include "biTree.h"

using namespace std;

//1.二叉树的遍历测试
void traversal_test() {
    TreeNode<char>* T;
    cout << "请按照先序顺序创建二叉树" << endl;
    create<char>(T);
    cout << "输出先序遍历顺序: " <<endl;
    vector<char> result;
    //测试先序遍历
    pre_traversal<char>(T, result);
    for (char i:result) {
        cout << i << ' ';
    }
    cout << endl;
    //测试中序遍历
    vector<char> result1 = in_Traversal(T);
    cout << "输出中序遍历顺序:" << endl;
    for (char i:result1) {
        cout << i << ' ';
    }
    cout << endl;
    //测试后序遍历
    vector<char> result2 = post_Traversal(T);
    cout << "输出后序遍历顺序:" << endl;
    for (char i:result2) {
        cout << i << ' ';
    }
    cout << endl;
}


#endif // BITREETEST_H_INCLUDED
