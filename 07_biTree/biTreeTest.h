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

//测试计算树高
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

//测试判断这个树是不是平衡二叉树
void getHeightTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //判断是不是平衡二叉树
    bool result = getHeight(T);
    cout << result << endl;
}

//测试获取一个树的所有路径
void binaryTreePathsTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //定义path
    vector<int> path;
    //定义result
    vector<string> result;
    //调用函数
    binaryTreePaths(T, path, result);
    for (string i :result){
        cout << i << endl;
    }
}

//测试计算一个二叉树的所有左叶子结点的value之和
void sumOFLeftLeavesTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //int result = sumOFLeftLeaves(T);
    int result = sumOFLeftLeavesDiedai(T);
    cout << result << endl;
}

//测试寻找二叉树最左下角节点的val
void findBottomLeftValueTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    findBottomLeftValue(T, 0);
    cout << my_result << endl;
}

//测试判断这个树中是否存在一个path，使得path上所有结点的val之和是target
void hasPathSumTest() {
    TreeNode<int>* T;
    cout << "请按照先序创建二叉树" << endl;
    create<int>(T);
    printLeave_oreder(T);
    //测试10
    bool result = hasPathSum(T, 10-T->val);
    cout << result << endl;
}

//测试通过中序和后序来构造一个二叉树
void buildTreeTest() {
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    TreeNode<int>* root = buildTree(inorder, postorder);
    printLeave_oreder(root);
}

//测试通过数组构造最大二叉树
void constructMaximumBinaryTreeTest() {
    vector<int> nums = {3, 2, 1, 6,0, 5};
    TreeNode<int>* root = constructMaximumBinaryTree(nums);
    printLeave_oreder(root);
}

//测试合并两个二叉树
void mergeTreesTest() {
    TreeNode<int> *t1, *t2, *result;
    //请输入第一个二叉树
    cout << "请输入第1个二叉树:"<<endl;
    create(t1);
    //请输入第二个二叉树
    cout << "请输入第2个二叉树:"<<endl;
    create(t2);

    result = mergeTrees(t1, t2);
    printLeave_oreder(result);
}

//测试在BST中搜索指定val的结点
void searchBSTTest() {
    TreeNode<int> *root, *result;
    create(root);
    printLeave_oreder(root);
    int val;
    cout << "请输入要查询的数字:" << endl;
    cin >> val;
    result = searchBST(root, val);
    cout << "最后查询的结果是:" << '\n' << result->val << endl;
}
#endif // BITREETEST_H_INCLUDED
