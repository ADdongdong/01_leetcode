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

//5.翻转二叉树（使用层序遍历）
template<class T>
TreeNode<T>* inverTree(TreeNode<T>* root) {
    //定义队列
    queue<TreeNode<T>*> que;
    //判断是否是空树
    if (root != NULL) que.push(root);
    while (!que.empty()) {
        //获取当前队列中元素的个数，也就是当前层元素的个数
        int s = que.size();
        for (int i = 0; i < s; i++) {
            //获取队头元素
            TreeNode<T>* node = que.front();
            que.pop();//删除队头元素
            swap(node->left, node->right);//翻转当前结点的左右孩子
            //只要对树中的没一个结点都进行了左右子树交换，最终就会得到翻转的效果
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return root;
}

//6.对称二叉树(递归)
template<class T>
bool compare(TreeNode<T>* left, TreeNode<T>* right) {
//使用递归方式完成对称二叉树的判断
/*
递归函数三部曲
1.确定递归函数的参数和返回值
2.确定终止条件
3.确定单层的递归逻辑
*/
/*
【整体逻辑整理】
   2
  3 3
4 5 5 6
以上面这个二叉树为例，我们要比价3,3位置，比较4,6位置，比较5,5位置
如果这几个位置比较结果都是相同的，那么这就是一个对称的二叉树，如果有一处不同就不是。
怎么比呢？过程是什么呢？
比较2的左节点和右边结点：这个比较可能会出现这么几种情况
①左右节点都存在，②左右节点都不存在，③左边存在右边不存在，④右边存在左边不存在。
很明显，③④这两种情况可以直接返回false了，对于这个结点这种情况出现必然不对称。
②这种情况，显然是检测通过的。①这种情况需要做进一步比较。

这两个结点比较完以后，要比较4和6，5和5，注意，4和6是分别是左孩子和右孩子，5和5是右孩子和左孩子
同理，如果有下一层也是要比较4的左孩子和6的右孩子，4的右孩子和6的左孩子。
然后不断递归进行比较。

【递归写法逻辑】
1.确定递归函数参数和返回值
参数：分别去往这个结点的左孩子和右孩子
返回值：bool，因为我们是要做判断

2.确定终止条件
也就是return 参考上面①②③④这几种情况

3.确定单层的递归的逻辑
对于每一层比较，我们要比较对应结点的左右孩子
*/
    //排有除空节点②③④
    if (left == NULL && right != NULL) return false;
    else if (left != NULL && right == NULL) return false;
    else if (left == NULL && right == NULL) return true;
    //如果都不是空节点，那么久盘看看这两个结点是不是一样的，如果不一样直接返回false
    //如果一样才继续执行后面的代码
    else if (left->val != right->val) return false;

    //这时候就是左右节点都不为空的情况，并且数值相同
    //这时候，我们才继续往下递归别的结点
    bool outside = compare(left->left, right->right);//
    bool inside = compare(left->right, right->left);
    bool isSame = outside && inside;
    return isSame;
}

//7.二叉树的最大深度/高度（递归）
template<class T>
int getdepth(TreeNode<T>* node) {
//二叉树结点的深度：从根节点到该结点的最长简单路径边的条数（从0开始数）或者节点数（从1开始数）
//二叉树节点的高度：指从该结点到叶子节点的最长简单路径边的条数或者节点数

//跟结点的高度->二叉树的最大深度

//递归三要素：
    //1.确定递归函数的返回值和参数：参数-传入根节点 返回值-int
    //2.终止条件：如果为空节点，返回0，表示高度为0
    if (node == NULL) return 0;
    //3.确定单层递归的逻辑
    int leftdepth = getdepth(node->left);//递归求左子树高度
    int rightdepth = getdepth(node->right);//递归求右子树高度
    int depth = 1 + max(leftdepth, rightdepth);//树的高度是根到叶子最长路径上的结点的数量
    //所以，每次要找最高的那个子树，所以要使用max函数
    //调用两个递归函数直接可以算出来两个子树的高度，取最高的子树就作为子树高度，再加上根节点高度就行
    return depth;//在这个题目中，我们认为的高度是从根节点到叶子节点最长路径上结点的数量
    //所以，如果这个二叉树只有一个节点，那么这个树的高度就是1
}
#endif // BITREE_H_INCLUDED
