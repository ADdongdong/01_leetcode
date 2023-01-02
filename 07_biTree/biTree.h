#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED
#include <iostream>
#include <vector>
#include <typeinfo>

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
void create(TreeNode<T>** treeNode) {
	cout << "please enter a number: " << endl;
	T data;
	cin >> data;
	char i = static_cast<char>(data);
	//cout << i << endl;
	if (i == '0') {
		*treeNode = NULL;
	}
	else {
		TreeNode<T>* node = new TreeNode<T>();
		*treeNode = node;
        (*treeNode)->val = data;
		create(&(*treeNode)->left);
		create(&(*treeNode)->right);
	}
}

//1.二叉树的前序遍历
template <class T>
void pre_traversal(TreeNode<T>* cur, vector<T>& vec){
    if (cur == NULL) return;//此时是空树，或者说空节点
    vec.push_back(cur->val);//将遍历到元素的数值添加到列表中
    pre_traversal(cur->left, vec);//先边递归遍历左子树
    pre_traversal(cur->right, vec);//先序递归遍历右子树
}

#endif // BITREE_H_INCLUDED
