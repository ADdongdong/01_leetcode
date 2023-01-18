#ifndef BITREETEST_H_INCLUDED
#define BITREETEST_H_INCLUDED
#include <iostream>
#include <vector>
#include "biTree.h"

using namespace std;

//打印层序遍历结果
template<class T>
void printLeave_oreder(TreeNode<T>* Tree){
    cout << "输出层序遍历的结果" << endl;
    vector<vector<T>> result3 = leave_Order(Tree);
    for (auto iterow = result3.begin(); iterow != result3.end(); iterow++){
            for (auto itcolumn = (*iterow).begin(); itcolumn != (*iterow).end(); itcolumn++) {
                cout <<  *itcolumn << ' ';
            }
            cout << endl;
        }
        cout << endl;
}

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
    printLeave_oreder(T);
}

//翻转二叉树测试
void invertTreeTest() {
    TreeNode<int>* T;//定义一个空树‘
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    cout << "翻转二叉树" << endl;
    TreeNode<int>* T_v = inverTree(T);
    printLeave_oreder(T_v);
}

//测试是否是对称二叉树
void compareTest() {
    TreeNode<int>* T;//定义一个空树
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //判断是否是对称二叉树
    bool result = compare(T->left, T->right);
    cout << result << endl;
}

//测试计算树高()
void getdepthTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //计算树的高度
    int result = getdepth(T);
    cout << "树的高度是" << result << endl;

}

//测试计算树的最小深度
void getmindepthTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //计算树的最小深度
    int result = getmindepth(T);
    cout << "树的最小深度是：" << result << endl;
}

//测试计算完全二叉树的结点个数
void getNumberDiedaiTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //计算树的最小深度
    int result = getNumberDiedai(T);
    cout << "完全二叉树的节点个数是：" << result << endl;
}
#endif // BITREETEST_H_INCLUDED
