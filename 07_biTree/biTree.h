#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED
#include <iostream>
#include <vector>
#include <typeinfo>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>


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
	TreeNode(T value):val(value), left(NULL), right(NULL){}
};

//前序递归创建二叉树
//如果输入-1代表这个结点为null
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
    //int depth = 1 + max(leftdepth, rightdepth);//树的高度是根到叶子最长路径上的结点的数量
    int depth = 1 + (leftdepth > rightdepth?leftdepth:rightdepth);//这样写和上面一样
    //所以，每次要找最高的那个子树，所以要使用max函数
    //调用两个递归函数直接可以算出来两个子树的高度，取最高的子树就作为子树高度，再加上根节点高度就行
    return depth;//在这个题目中，我们认为的高度是从根节点到叶子节点最长路径上结点的数量
    //所以，如果这个二叉树只有一个节点，那么这个树的高度就是1
}

//8.二叉树的最小深度(后序遍历)
template<class T>
int getmindepth(TreeNode<T>* node) {
//这里要注意深度和高度的区别
//树的深度是从根到叶子节点路径上边的条数(从0开始)或者结点的个数（从1开始）
//树的高度是从根到距离根最远的那个结点路径上边的条数(从0开始)或者结点的个数(从1开始)
//所以，如果这个二叉树只有两个节点，那么，这个树的最小深度是2，不是1，因为只有一个叶子节点
//所以，如果左子树为空，那么树最小深度就是右子树的最小深度+1

    //递归函数三部曲
    //1.确定函数返回值和参数
    //2.确定函数返回值
    if (node == NULL) return 0;//如果为空树，返回0
    //递归计算左子树深度
    int leftheight = getmindepth(node->left);
    //递归计算右子树深度
    int rightheight = getmindepth(node->right);

    //由于深度的特性，处理根节点左右子树分别为空的情况
    if (node->left == NULL && node->right != NULL) {
        return 1 + rightheight;
    }
    if (node->left != NULL && node->right == NULL) {
        return 1 + leftheight;
    }

    //计算最终的结果
    int result = 1 + min(leftheight, rightheight);//在根节点左右子树中寻找一个深度最小的树
    return result;
}

//8.1 二叉树的最小深度(迭代)
template<class T>
int mindepth(TreeNode<T>* node) {
    if (node == NULL) return 0;
    int depth = 0;
    queue<TreeNode<T>*> que;
    que.push(node);
    while (!que.empty()) {
        //使用层序进行遍历，找最靠近根的那个叶子节点
        int size = que.size();
        depth++;//记录最小深度
        //使用迭代法找最小深度的时候，第一个最上一层高的最靠近根节点的第一个叶子节点
        //到根节点的的深度就是 这个树的最小深度，所以，depth更新到最近叶子节点的时候就返回了
        for (int i = 0; i < size; i++) {
            TreeNode<T>* node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
            if (!node->left && !node->right) {
                //当左右节点都为空的时候，说明遇到了距离根节点最近的第一个叶子结点
                //这个叶子节点到根节点的距离就会最小深度
                return depth;
            }
        }
    }
    return depth;//这里返回的是空树的depth因为执行不到while训练里面的内容
}

//9.完全二叉树的节点个数【递归】
template<class T>
int getNumber(TreeNode<T>* cur) {
//思路：可以采用后序遍历，先找到左子树节点，再找到又子树结点
//最后左右子树结点相加再加一就是最终二叉树的结点的个数
//递归三部曲
//1.返回值-int,参数结点-node
//2.终止条件，如果cur==NULL return 0
    if (cur==NULL) return 0;
    int lefnumber = getNumber(cur->left);
    int rightnumber = getNumber(cur->right);
    //计算最终整个树的结点个数
    int sum = 1 + lefnumber + rightnumber;
    return sum;
}

//9.1 计算完全二叉树的结点个数【迭代法】
template<class T>
int getNumberDiedai(TreeNode<T>* cur) {
    //使用层序遍历
    if (cur == NULL) return 0;//如果是空树，直接返回0
    //定义队列
    queue<TreeNode<T>*> que;
    //根节点进入队列
    que.push(cur);
    //定义result
    int result = 0;
    //while训话
    while (!que.empty()) {
        int size = que.size();//注意，层序遍历for循环中，每次只取到上一层的左右孩子结点
        //所以遍历的个数就是上一层结点的个数。每次队列只保存一层结点。
        for (int i = 0; i < size; i++) {
            //获取队头结点
            TreeNode<T>* node = que.front();
            que.pop();//删除刚才获取到的结点
            result++;//每出队一个结点，就result++
            //刚才出队左孩子入队
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return result;//返回最终的结果
}

//10. 判定一个树是不是平衡二叉树【递归法】
template<class T>
int getHeight(TreeNode<T>* node) {
//平衡二叉树的定义：一个二叉树每个节点的左右两个子树的高度差绝对值不超过1
//二叉树节点的高度：指从该结点到(距离最远的)叶子节点的最长简单路径边的条数或者节点数
//思路：这个题目就是要对每一个节点进行比较，比较其两个子树的高度，如果所有的节点都满足，则树满足
    //1.明确函数返回值和参数
    //函数返回值：如果为平衡二叉树，返回树的高度，如果不是，返回-1
    //参数：TreeNode<T>*
    //2.终止条件
    if (node == NULL) return 0;

    //递归遍历左子树
    int leftheight = getHeight(node->left);
    //递归遍历右子树
    int rightheight = getHeight(node->right);

    //左右子树进行比较
    int result;
    if (abs(leftheight- rightheight) > 1) {
        return -1;
    } else {
        result =  1 + max(rightheight,leftheight);//如果树正常，则左右子树中最高的树的高度+1为整个树的高度
    }
    return result;
}

//11.二叉树的所有路径【递归法】
template<class T>
void binaryTreePaths(TreeNode<T>* cur, vector<T>& path, vector<string>& result) {
//采用先序遍历的方式进行操作
//1.返回值和参数
//2.终止条件
//3.每一层迭代的逻辑

/*
思路：
先序遍历，每次遇到一个结点，就将这个结点放入path中
每次遍历到一个叶子节点的时候，就会得到一个路径
所以，每次得到一个路径就把这个路径加入result中，
这时候，要将path中刚才加入reusult的那些结点都删除了，也就是回溯
然后，找下一个path，直到遇到下一个叶子结点
result保存了所有的路径
*/

    path.push_back(cur->val);//将遍历到这个节点的val加入到当前的path

    //到叶子结点以后，就将当前path稍作修饰，加入result
    if (cur->left == NULL && cur->right == NULL) {
        string sPath;
        //给每一个节点后面加上->
        for (int i = 0; i < path.size() - 1; i++){
            sPath += to_string(path[i]);
            sPath += "->";
        }
        //将path中最后一个元素加入到sPath中
        sPath += to_string(path[path.size() - 1]);
        //将刚才处理好的sPath加入到result
        result.push_back(sPath);
        return;
    }
    //递归遍历左子树
    if (cur->left) {
        binaryTreePaths(cur->left, path, result);
        //回溯
        path.pop_back();
        //当执行到回溯代码的时候，已经将第一个path加入到result中了
        //此时，要将path中的叶子结点pop了，继续往下检查(遍历右子树)
        //看叶子节点的父节点还有没有右孩子，如果有，则就是新的path
        //如果没有，则会继续回溯继续删除path中的元素，直到找到有右孩子的
        //或者一直删除完,一层一层迭代删除完
    }

    //递归遍历右子树
    if (cur->right) {
        binaryTreePaths(cur->right, path, result);
        //回溯
        path.pop_back();
    }
}

//12.1计算给定二叉树的所有左叶子结点之和【递归法】
template<class T>
int sumOFLeftLeaves(TreeNode<T>* node) {
    //递归遍历来求二叉树的所有左叶子节点
    //采用后序遍历，左右中
    //先递归求左子树的左叶子节点个数，再递归遍历求有子树所有左叶子节点个数
    //最后对两个值求和就是最终的结果了

    //递归三部曲
    //1.返回值和参数:返回值int返回的是所有左叶子结点的个数，参数是树指针
    //2.终止条件:
    //2.1 这是一个空树
    if (node == NULL) return 0;
    //2.2 这个树的左右节点都是空节点，即，只有一个根节点
    if (node->left==NULL && node->right==NULL) return 0;

    //递归遍历左子树
    int leftValue = sumOFLeftLeaves(node->left);

    //检查这个节点的左子树是不是左叶子，如果是左叶子就赋值给leftValue
    //是一个左子树，有左孩子，没有右孩子，而且左孩子的左右节点都是空节点
    if (node->left != NULL && node->left->left == NULL && node->left->right == NULL) {
        leftValue = node->left->val;//此时，左子树上的叶子结点的数字就求出来了
    }

    //递归遍历右子树
    int rightValue = sumOFLeftLeaves(node->right);

    //计算左右子树所有叶子结点value之和
    //递归遍历中间结点
    int sum = leftValue + rightValue;
    return sum;
}

//12.2计算给定二叉树的所有的做叶子结点之和【迭代发】
template<class T>
int sumOFLeftLeavesDiedai(TreeNode<T>* node) {
    //使用迭代法很简单，这里使用栈，每次出栈一个结点，只要检查这个结点是不是左叶子结点就行了
    stack<TreeNode<T>*> st;//定义一个栈
    //如果树不为空，进栈
    if (node != NULL) st.push(node);
    //定义result来保存最后的结果
    int result = 0;
    //while循环,采用先序遍历的迭代算法
    while (!st.empty()) {
        //栈顶元素出栈（中）
        TreeNode<T>* node = st.top();
        st.pop();
        //判断出栈的这个元素的左孩子是不是左叶子结点
        //注意，不是判断这个元素是不是左叶子
        if (node->left != NULL && node->left->left == NULL && node->left->right == NULL) {
            //如果是左叶子，那么就加入到result中
            result += node->left->val;
        }
        //这个结点的右孩子进队
        if (node->right) st.push(node->right);
        //左孩子进队
        if (node->left) st.push(node->left);
    }
    return result;
}

//13.1找树左下角的值
//定义两个全局变量
int maxDepth = INT_MIN;//maxDepth变量用来保存遍历到现在深度最大叶子节点的深度
int my_result;//result用来保存最后的结果
template<class T>
void findBottomLeftValue(TreeNode<T>* node, int depth) {
    //递归三部曲
    //1.返回值和参数
    //返回值肯定是int,参数depth用来保存当前最大深度叶子结点的深度
    //2.终止的条件
    //如果是叶子结点就查看其节点的深度，如果是最深，则更新result的值
    if (node->left == NULL && node->right == NULL) {
        //如果当前深度大于maxDepth则更新my_result
        if (depth > maxDepth) {
            maxDepth = depth;
            my_result = node->val;
        }
        return;
    }
    //3.单层递归的逻辑
    //递归遍历左子树
    if (node->left) {
        depth++;//每向下遍历一个结点，则当前节点的深度++
        findBottomLeftValue(node->left, depth);
        depth--;//回溯，遍历完当前节点(当前子树)以后，回退到上一层，深度-1
    }

    if (node->right) {
        depth++;
        findBottomLeftValue(node->right, depth);
        depth--;
    }
    return;
}

//13.2找树左下角节点的值【迭代】
template<class T>
int findBottomLeftValueDiedai(TreeNode<T>* root){
//使用层序，只要返回最后一层的第一个节点的value
    queue<TreeNode<T>*> que;
    if (root != NULL) que.push(root);
    int result;//定义result保存最后得结果
    while(!que.empth()){
        int size = que.size();//保存当前层节点的个数
        for (int i = 0; i < size; i++) {
            //获取队头
            TreeNode<T>* node = que.front();
            que.pop();
            //获取每一层第一个结点的值
            //每遍历新的一层都会更新result的值，最后返回的result就是最后一层最左边的result
            if (i==0) result = node->val;
            if (node->left) que.push(node->left);
            if (node->right) que.puh(node->right);
        }
    }
    return result;
}

//14 判断这个二叉树中是否存在一条路径，这个路径上结点value之和等于给定的target
template<class T>
bool hasPathSum(TreeNode<T>* root, int _count) {
    //1.返回值和参数
    //2.递归终止的条件
    //当遍历到了叶子结点，则对其进行判断，判断是否以这个结点为结尾的路径是目标路径
    //给定的_count就是目标target,每遍历一个结点，就减去对应结点的value值
    //如果遍历到某个叶子结点_count被减到了0，则说明存在Path返回true，否则返回false
    if ( root->left == NULL && root->right == NULL && _count == 0) return true;
    if ( root->left == NULL && root->right == NULL && _count != 0) return false;

    //递归遍历左子树
    if (root->left) {
        _count -= root->left->val;
        if (hasPathSum(root->left, _count)) return true;
        _count += root->left->val;//如果没有return true，就要回溯，继续寻找满足条件的path
    }

    //递归遍历右子树
    if (root->right) {
        _count -= root->right->val;
        if (hasPathSum(root->right, _count)) return true;
        _count += root->right->val;//回溯
    }

    return false;//如果没有返回true, 则返回false
//经过本题目，对回溯的理解
/*
什么时候回溯？
如果一个倒数第二层的结点有两个叶子节点，其中一个叶子节点所在的路径是target，另个一不是
那么，如果先检查到不是target的那个节点，然后要去检查第二个结点，那第二个结点使用从root再重新寻找吗？
当然不是，只要取到这个叶子结点的父节点，然后从父节点再往下找就行了。
从叶子到父节点这个过程就是回溯，递归遍历是自带回溯的(这个回溯的过程需要自己手推递归遍历)。
但是，我们要让参数_count也保持回溯，那就要
把代码写出来。就是下面两行
_count -= root->right->val;
_count += root->right->val;
*/
}

//15 根据一棵树的中序遍和后序遍历历构造二叉树
template<class T>
TreeNode<T>* buildTree(vector<T>& inorder, vector<T>& postorder) {
    //第一步:判断这是不是一个空树
    if (postorder.size() == 0) return NULL;

    //第二步：后序遍历数组最后一个元素，就是当前树的根节点,并创建相应根节点
    int rootValue = postorder[postorder.size() - 1];
    TreeNode<T>* root = new TreeNode<T>(rootValue);

    //如果先序遍历序列中只有一个元素，那么这个结点就是整个二叉树
    if (postorder.size() == 1) return root;

    //第三步：找到中序遍历的切割点
    int delimiterIndex;
    for (delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex++) {
        if (inorder[delimiterIndex] == rootValue) break;//此时，delimiterIndex的值就是切割点下标
    }

    //第四步：切割中序数组，得到 中序左数组和中序右数组
    //左闭右开区间 [0, delimiterIndex) 略过了切割元素
    vector<T> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);//这样是根据传入参数，左闭右开来构造vectorde
    //左闭右开区间 [delimiterIndex + 1, end)
    vector<T> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());//end()终止迭代器，是最后一个元素下标的后一个位置
    //所以，如果构造函数第二个参数是end(),那么是可以取到inorder的，不用担心左闭右开把最后一个元素忽略的情况



    //postorder(后序数组)要舍弃末尾元素，因为，后序遍历的最后一个结点就是跟结点
    //在刚才的处理中已经放到二叉树中了，下一次迭代就不能使用了，所以要size-1
    postorder.resize(postorder.size() - 1);

    //第五步：切割后序数组，得到 后序左数组和后序右数组
    //依然使用左闭右开，这里使用左中序数组大小作为切割点
    //[0, leftInorder.size),前面leftInorder.size个元素都是中序遍历左子树的元素
    vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
    //[leftInorder.size, end)
    vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

    //第六步：递归建立左子树和右子树
    root->left = buildTree(leftInorder, rightInorder);
    root->right = buildTree(leftPostorder, rightPostorder);

    return root;
}

//16 最大二叉树【给定一个列表，去根据这个列表构造最大二叉树】
template<class T>
TreeNode<T>* constructMaximumBinaryTree(vector<T>& nums){
    //1.确定函数返回值和参数
    //2.确定递归终止的条件
    //当检测到nums只有一个元素的时候，说明要么到了叶子结点，要么是根节点
    //此时需要构建一个新的结点，将max值放到新的结点中
    TreeNode<T>* node = new TreeNode<T>(0);
    if (nums.size() == 1) {
        node->val = nums[0];
        return node;//返回这个叶子结点的指针
    }

    //3.单层遍历的逻辑
    //3.1 找到当前数组中最大元素对应的下标，用最大的值来构造根节点，并用最大的值来切分数组
    int maxValue = 0;
    int maxValueIndex = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > maxValue) {
            maxValue = nums[i];
            maxValueIndex = i;
        }
    }
    //将刚才找到了max值放在新创建的node中
    node->val = maxValue;
    //3.2 最大值所在的下标左区间，构造左子树
    //要保证构造子树的那个数组区间中至少有一个元素
    if (maxValueIndex > 0) {
        //当刚才记录到的maxValueIndex>0的时候，说明最大值左边区间至少有一个元素
        vector<T> newVec(nums.begin(), nums.begin() + maxValueIndex);//切割出来的这个区间是不包括maxValue的
        node->left = constructMaximumBinaryTree(newVec);//用左边区间递归创建左子树
    }

    //3.3 最大值所在的下标右区间，构造右子树
    if ((nums.size() - maxValueIndex) > 1) {
        vector<T> newVec(nums.begin() + maxValueIndex + 1, nums.end());
        node->right = constructMaximumBinaryTree(newVec);
    }
    return node;
}

//17 合并二叉树
template<class T>
TreeNode<T>* mergeTrees(TreeNode<T>* t1, TreeNode<T>* t2) {
    //1 确定函数的返回值和参数
    //2 确定终止的条件
    //在对叶子结点的处理上，可以把合并树理解为取并集，哪个有，就取哪个结点
    if (t1 == NULL) return t2;
    if (t2 == NULL) return t1;
    //3 单层递归逻辑
    //3.1 如果遍历到这个位置两个结点都不是NULL，那么就要将这两个结点的value相加
    //    (我们这里将t1作为一会要返回的树)
    t1->val += t2->val;
    //3.2 递归处理t1,t2的下一个结点
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);

    return t1;//最后返回t1
}

//18 在二叉搜索树(BST)中搜索给定value的结点
template<class T>
TreeNode<T>* searchBST(TreeNode<T>* root, int val) {
    //1. 确定函数的返回值和参数
    //返回值：因为要判断指定value的结点是否在BST中，如果在，返回的是指定val的结点
    //参数：当然必定有一个参数要给定val，另一个给定在那个BST中查找

    //2. 递归终止的条件
    //当访问到空或者val的时候终止当前递归
    if (root == NULL || root->val == val ) return root;

    //3. 单层遍历的逻辑
    //注意，这里是在BST中搜索，所以，就可以用类似二分查找的逻辑去寻找指定的val
    TreeNode<T>* result = NULL;//首先给最终的结果赋值为NULL,因为如果最后递归完了还没找到，就只能返回NULL了
    //如果找到了，自然会返回响应的root
    if (root->val > val) result = searchBST(root->left, val);
    if (root->val < val) result = searchBST(root->right, val);

    return result;//返回最终的result
}

//19 验证二叉搜索树
long long maxVal = LONG_MIN;
template<class T>
bool isValidBST(TreeNode<T>* root) {
    if (root == NULL) return true;

    //递归处理左子树
    bool left = isValidBST(root->left);
    //中序遍历处理中间结点
    //中间结点的处理就是承前启后，中间结点要和跟刚才左子树相比，如果比左大，说明左->中的顺序是合理的
    //同时，要将此时中间结点的val赋值给maxVal，因为，这个值要和右结点做同样的比较
    //如果，左大于中间，则说明这个二叉搜索树是错误的，返回false
    if (maxVal < root->val) maxVal = root->val;//maxVal保存前一个访问过的结点，中序遍历，只要前一个访问节点一直小于后一个访问节点就可以了
    else return false;

    //递归遍历右子树
    bool right = isValidBST(root->right);

    //返回的最终结果是左右子树返回的bool值取交集，这样整个树只要有一个false就会返回false
    return left && right;
}

//20 二叉搜索树的最小绝对值差
int result = INT_MAX;
TreeNode<int>* pre = NULL;
template<class T>
void getMinimumDifference(TreeNode<T>* cur) {
    //思路：在二叉搜索树中找最小绝对值之差，首先，中序遍历二叉搜索树得到的是一个递增的序列
    //所以，二叉搜索树的最小绝对值之差只会在相邻两个结点出现，不可能说是间隔两个结点的差值比相邻的还小
    //1.返回值和参数
    //2.递归终止的条件
    if (cur == NULL) return;

    //3.1递归遍历左子树
    getMinimumDifference(cur->left);

    //3.2递归处理中间结点
    //计算中间结点和上一个结点val的差值，这个差值和result之间取最小的作为新的result
    if (pre != NULL) {
        result = min(result, cur->val - pre->val);
    }
    pre = cur;//pre指针按顺序往后移动一个结点

    //3.3递归遍历右子树
    getMinimumDifference(cur->right);
}

//21 二叉搜索树中的众数字
int maxCount = 0;
int Count = 0;
TreeNode<int>* pre_21 = NULL;
vector<int> result_21;
template<class T>
void findMode(TreeNode<T>* cur) {
//思路:
/*
    二叉搜索树的中序遍历序列是由小到大的递增序列。
    所以， 和上一个题目一样，仍然是一个cur指针，一个pre指针。
    如果cur和pre所指向结点的val相同，那么当前val的Count就++，并且，当前Count和maxCount做比较。
    如果当前Count等于maxCount就讲过当前的val加入到result中。
    如果当前Count大于maxCount，那么就清空result,并更新maxCount，在将当前val加入到result中。
    如果当前Count小于maxCount那就继续遍历，不做任何操作。
    maxCount：记录的是当前出现最多的元素所出现的次数。
    Count：记录的是当前cur所指向的val出现的次数。
    result：记录的是出现次数等于maxCount的val。如果maxCount更新，result也要清除更新。
*/
    //1.返回值和参数
    //2.递归终止的条件
    if(cur == NULL) return ;

    //3.1 递归遍历左子树
    findMode(cur->left);

    //3.2 递归遍历中间结点
    if (pre_21 == NULL) {
    //当pre为NULL的时候，说明cur正在遍历第一个结点
        Count = 1;//此时cur所指的val出现了1次
    } else if (pre_21->val == cur->val) {
    //当cur与前一个结点相同的时候，就Count++
        Count++;
    } else {
    //当个cur与前一个结点不同的时候,Count继续置为1
    }

    //当当前遍历结点的val出现次数到达当前的maxCount，那么就将当前cur指向的val加入result
    if (Count == maxCount) {
        result_21.push_back(cur->val);
    }

    //当当前遍历结点的val出现次数大于当前maxCount是，更新maxCount和result
    if (Count > maxCount) {
        maxCount = Count;
        result_21.clear();
        result_21.push_back(cur->val);
    }
    pre_21 = cur;//处理完中间结点要更新pre的值

    //3.3 递归遍历右子树
    findMode(cur->right);
    return;
}

//22 二叉树的最近公共祖先
template<class T>
TreeNode<T>* lowestCommonAncestor(TreeNode<T>* root, TreeNode<T>* p, TreeNode<T>* q) {
//思路
/*
    题目给了两个二叉树结点的指针，要返回这两个指针的最近的公共祖先。
    首先，这个题只能使用后序遍历，左右中。因为后序是先访问两个叶子，再访问中间结点。
    那根据后序遍历的访问顺序怎么操作呢？
    我们将后序每个结点后序左右子树遍历的结果保存在left和right中。
    如果有p那left保存的就是p
    (只要左子树出现p就，整个左子树返回的就是p，q同理，右子树同理，如果p,q都没有出现，就返回NULL)

    这样，对每一个结点都可以得到这个结点左右子树返回来的值。
    我们就根据这个结点左右子树返回来的值来判断这个结点是不是p，q的最近公共结点。
    怎么判断呢？左右子树可能跟返回如下三个值：p, q, NULL
    那么请问，一个结点的左右子树满足那种情况的时候，这个结点是p, q的最近公共祖先呢？
    当然只有两种情况：left:q, right:p 和left:p, right:q这两种情况了。
    所以，这时候只需要做判断，如果左右子树返回的都不是NULL那么，当前处理的这个结点就是p,q的最近公共祖先了。
    结束。
*/
    //1.返回值和参数：返回值仍然是Treenode
    //2.递归终止的条件
    /*什么时候递归终止？
     2.1 当前访问的结点是p或者q
     2.2 当前访问到了空节点NULL(这个树是空树，或者叶子结点的孩子)
    */
    if (root == q || root == p || root == NULL) return root;//对叶子结点的处理
    //3.单层递归处理逻辑
    //3.1 后序遍历左子树
    TreeNode<T>* left = lowestCommonAncestor(root->left, p, q);
    //3.2 后序遍历右子树
    TreeNode<T>* right = lowestCommonAncestor(root->right, p, q);
    //3.3 后序遍历处理中间结点

    //问题：这里为什么判断的是左右子树返回值不为NULL，为什么不判断左右子树返回值是p,q?
    /*
        因为，我们要向上传递的是四种值：NULL,p,q,最近公共祖先
        如果，判断是左右子树返回的是否是p,q那么，如果左右子树有一个子树出现了【最近公共祖先】
        那这个结果会因为不是p,q而传递不上去。
        反之，我们之和NULL做比较，只要不是NULL的都往上传，那无论在哪里找到了【最近公共祖先】
        都会被递归返回上去。
    */
    //得到了这个结点左右子树的值，就要判断这个结点是不是p,q的最近公共结点了
    if (left != NULL && right != NULL) return root;//左右子树都不为空，说明左右子树返回的是p,q或者q,p具体顺序我们不关心

    if (left != NULL && right == NULL) return left;//一个不为空，返回不为空的那个
    else if (left == NULL && right != NULL) return right;//同理
    else {
        return NULL;//只剩下最后一种情况，左右两边都返回的是NULL
    }

}

//23 二叉搜索树的最近公共祖先
template<class T>
TreeNode<T>* lowestCommonAncestorBST(TreeNode<T>* cur, TreeNode<T>* p, TreeNode<T>* q) {
    //1.返回值和参数
    //2.递归终止的条件
    if (cur == NULL) return cur;
    //3.单层递归遍历的逻辑
    //这是二叉搜索树，是有序的,所以p和q的最近公共祖先只可能在p和q的中间
    //如果当前遍历的结点在p,q的右边，那就要向左边遍历，说明目标在左边
    if (cur->val > p->val && cur->val > q->val) {
        TreeNode<T>* left = lowestCommonAncestorBST(cur->left, p, q);
        if (left != NULL) {
            return left;
        }
    }

    //如果当前遍历的结点在p,q的左边，那就要向这个几结点的右边遍历，说明目标在右边
    if (cur->val < p->val && cur->val < q->val) {
        TreeNode<T>* right = lowestCommonAncestorBST(cur->right, p, q);
        if (right != NULL) {
            return right;
        }
    }

    //如果，上面两个if都没有执行，说明当前cur在p和q的中间，就是我们要求的目标值
    return cur;
}

//24 二叉搜索树中的插入操作
template<class T>
TreeNode<T>* insertIntoBST(TreeNode<T>* root, int val) {
    //1.确定返回值和参数
    //2.递归终止的条件
    if (root == NULL) {
        //如果遍历到了空结点，说明可以再这里插入新的结点了
        TreeNode<T>* node = new TreeNode<T>(val);
        return node;
    }
    //3.确定单层结点的逻辑
    if (root->val > val) root->left = insertIntoBST(root->left, val);//下一层返回的node指针我们用叶子结点左指针来接住
    if (root->val < val) root->right = insertIntoBST(root->right, val);
    return root;
}

//25 删除二叉搜索树中的结点
template<class T>
TreeNode<T>* deleteNode(TreeNode<T>* root, int key) {
    //2.递归终止的条件，没有找到要删除的目标结点，返回NULL
    if (root == NULL) return root;

    //3.单层处理的逻辑，这里采用先序遍历处理
    if (root->val == key) {
        //3.1 找到要删除的结点了，这个结点没有左右孩子,直接删除这个结点
        if (root->left == NULL && root->right == NULL) {
            //要释放这个结点的内存
            delete root;
            return NULL;
            //为什么要返回NULL,是为了让删除节点的父节点接住，也就是说，将父节点的孩子置为NULL了
            //这个return NULL在回溯的过程中才会体现出来。
        }
        //3.2 左孩子为空，右孩子不为空，删除结点，右孩子补位置，返回右孩子，作为删除结点父节点的孩子
        else if (root->left == NULL) {
            TreeNode<T>* retNode = root->right;//保存右孩子
            delete root;//删除遍历结点
            return retNode;//返回刚才保存的右子树的父节点
        }
        //3.3 左孩子不为空，右孩子为空，删除结点，左孩子补充位置，返回左孩子作为删除节点父节点的孩子
        else if (root->right == NULL) {
            TreeNode<T>* retNode = root->left;
            delete root;
            return retNode;
        }
        //3.4 左右孩子都不为空，将删除结点的左子树放在删除结点右子树的最左边结点的左子树上
        //    返回删除结点右子树的根节点
        else {
            TreeNode<T>* retNode = root->left;
            //寻找右子树的最左结点
            TreeNode<T>* cur = root->right;
            while (cur->left != NULL) {
                cur = cur->left;//一直寻找右子树的左子树，知道找到空节点，也就是最左结点的左子树，此时为空
            }
            //将待删除结点的左子树放在刚才找到cur的左子树位置上
            cur->left = retNode;
            //保存待删除的root
            TreeNode<T>* tmp = root;
            root = root->right;//待删除结点右待删除结点的右子树所代替
            delete tmp;//删除待删除结点【注意，这里千万不能删除root，因为此时root已经是待删除结点的右子树了】
            return root;//返回新的root
        }
    }

    //如果当前遍历的结点大于要删除的目标值，要往当前结点的左边找，找比当前结点小的值
    if (root->val > key) root->left = deleteNode(root->left, key);
    //如果当前遍历的结点小于要删除的目标值，要往当前结点的右边找，找比当前结点大的值
    if (root->val < key) root->right = deleteNode(root->right, key);

    return root;//返回root
}

//25 修剪二叉搜索树
template<class T>
TreeNode<T>* trimBST(TreeNode<T>* root, int low, int height){
    //1.返回值和参数
    //2.递归终止的条件
    if (root == NULL) return NULL;

    //3.单层递归的逻辑(为什么这里说是单层，因为，递归函数，就像一个宝塔，每一个结点带入都是新的一层)
    //3.1 如果当前结点的val小low
    if (root->val < low) {
        //如果当前结点小于low,说明，应该往这个结点的右边去找，去这个结点的右子树上找一个合适的结点
        //用右子树上再low到height之间的合适子树来代替root
        TreeNode<T>* right = trimBST(root->right, low, height);
        return right;//将这层寻找的结果返回给上一层
    }

    //3.1 如果当前结点的val大于height
    if (root->val > height) {
        //如果当前结点的val大于height，说明应该往这个结点的左边去寻找
        //找左子树上小于val的在low到height之间的子树来代替当前结点
        TreeNode<T>* left = trimBST(root->left, low, height);
        return left;//将这个结点左子树找到的结果返回给上一层
    }

    //如果当前结点是在low和height之间的结点，那就修剪这个结点的左右子树
    root->left = trimBST(root->left, low, height);
    root->right = trimBST(root->right, low, height);
    return root;//返回这个结点(子树/树)
}

//26 将有序数组转化为二叉树
template<class T>
TreeNode<T>* sortedArrayToBST(vector<T>& nums, int left, int right) {
    //1.返回值和参数
    //返回值是TreeNode<T>*类型，返回的其实是子树根的指针
    //参数：第一参数是当前递归生成子树的数组引用，第二三个参数是这个数组分段的做下标和右下标
    /*理解：我们要将nums这个参数转化成而二叉搜索树，肯定是先选取中间结点，
            然后，将以这个中间结点划分出来的左右区间，再次作为数组，进行递归生成子树。
            这里，我们每次递归传入的起始都是原来那个数组的引用，我们也没有对原来的数组进行修改。
            但是，每次递归到下一层还要对数组进行划分成子数组，这里用的方法就是传入子数组在nums中的下标范围。
    */
    //2.递归终止的条件
    //当这个子数组做下标大于由下标，说明这个子数组是空数组，返回NULL
    if (left > right) return NULL;

    //3.单层遍历的逻辑
    //3.1 找到当前数组的中间结点下标
    int mid = left + ((right-left)/2);//这样是防止int溢出
    //3.2 生成新的结点，并将中间结点赋值给这个新的结点
    TreeNode<T>* root = new TreeNode<T>(nums[mid]);
    //3.3 递归生成root的左子树
    root->left = sortedArrayToBST(nums, left, mid-1);
    //3.4 递归生成root的右子树
    root->right = sortedArrayToBST(nums, mid+1, right);

    return root;//返回这个树
}

//27 把二叉搜索树转化成累加树
int pre_27 = 0;//用pre来记录上一个结点计算出来的结果
void convertBST(TreeNode<int>* cur){
    //这个函数只是对树中每个节点的值做修改，所以，没有返回值
    //按照从大到小的顺序遍历，顺序为右->根->左
    //将右+根赋值给根
    if (cur == NULL) return;//没有返回值

    //递归遍历右子树
    convertBST(cur->right);
    //递归处理中间结点

    cur->val = cur->val + pre_27;//pre记录的是上一个遍历修改过的结点
    pre_27 = cur->val;
    //递归遍历左子树
    convertBST(cur->left);
}

#endif // BITREE_H_INCLUDED
