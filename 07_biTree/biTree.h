#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED
#include <iostream>
#include <vector>
#include <typeinfo>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;

/*
递归算法的三要素：
1.确定递归函数的返回值和参数：
①确定哪些参数是递归过程中需要处理的，那么就在递归函数里加上这个参数
②明确每次递归的返回值是什么而确定递归函数的返回值类型

2.确定终止条件
3.确定单层递归的逻辑
*/

//定义二叉树的基本结构
template <typename T>
class TreeNode {
public:
	T val;
	TreeNode* left;
	TreeNode* right;
	TreeNode():val('0'), left(NULL), right(NULL){}

};

//前序递归创建二叉树
template <class T>
void create(TreeNode<T>* &treeNode) {
    //传入的参数是一个指针的引用，这样，可以保证这个指针可以被改变
    //如果只传入一个指针，则这个指针不会被改变，
	cout << "please enter a number: " << endl;
	T data;
	cin >> data;
	//如果是字符二叉树，输入0表示这个位置为空节点
	//如果是数字二叉树，输入-1表示这个位置为空节点
	if (data == '0' || data == -1) {
		treeNode = NULL;
	}
	else {
		TreeNode<T>* node = new TreeNode<T>();
		treeNode = node;
        treeNode->val = data;
		create(treeNode->left);
		create(treeNode->right);
	}
}

//1.二叉树的前序遍历（递归）
template <class T>
void pre_traversal(TreeNode<T>* cur, vector<T>& vec){
    if (cur == NULL) return;//此时是空树，或者说空节点
    vec.push_back(cur->val);//将遍历到元素的数值添加到列表中
    pre_traversal(cur->left, vec);//先边递归遍历左子树
    pre_traversal(cur->right, vec);//先序递归遍历右子树
}

//2.二叉树的中序遍历(迭代)
template<class T>
vector<T> in_Traversal(TreeNode<T>* root) {
    //定义一个栈用，用于让扫描到的结点进栈
    stack<TreeNode<T>*> st;
    //定义vector保存最后遍历的结果
    vector<T> result;
    TreeNode<T>* cur = root;
    while (cur != NULL || !st.empty()) {
        //首先扫描到最最小角落的结点
        if (cur!=NULL) {
            //扫描到的结点进栈
            st.push(cur);
            cur = cur->left;
        } else {
        //已经扫描到最最左下角的结点了，那就开始遍历，按照左中右
            cur = st.top();
            st.pop();
            //结点加入遍历列表
            result.push_back(cur->val);
            //开始遍历这个结点的右子树
            cur = cur->right;
        }
    }
    return result;
}

//3.二叉树的后序遍历(迭代)
template<class T>
vector<T> post_Traversal(TreeNode<T>* root) {
    //定义栈
    stack<TreeNode<T>*> st;
    //定义vector保存遍历结果
    vector<T> result;
    //判断是否为空树
    if (root == NULL) return result;
    //不为空树，根节点入队
    st.push(root);
    //进入循环，处理整个树
    while (!st.empty()) {
    //只要栈不为空就继续遍历
        //获取栈顶元素
        TreeNode<T>* node = st.top();
        st.pop();//删除刚才已经获取到的元素
        result.push_back(node->val);
        //先扫描左，左先进栈，先进栈的后出栈
        if (node->left) st.push(node->left);
        if (node->right) st.push(node->right);
    }
    //result顺序翻转
    reverse(result.begin(), result.end());
    return result;
}

//4.二叉树层序遍历(迭代)
template<class T>
vector<vector<T>> leave_Order(TreeNode<T>* root) {
    vector<vector<T>> result;
    queue<TreeNode<T>*> que;
    //判断是否为空树
    if(root != NULL) que.push(root);
    while (!que.empty()) {
        int s = que.size();//保存当前队列的长度
        //也就是上一层所有元素，然后对下一层所有元素遍历其双孩子
        vector<int> vec;
        //这里使用固定大小的size,不使用que.size
        //遍历上一层进入队列的所有元素
        for (int i = 0; i < s; i++) {
            TreeNode<T>* node = que.front();
            que.pop();
            vec.push_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        result.push_back(vec);
    }
    return result;
}

//5.翻转二叉树

#endif // BITREE_H_INCLUDED
