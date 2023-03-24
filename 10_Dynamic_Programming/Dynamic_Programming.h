#ifndef DYNAMIC_PROGRAMMING_H_INCLUDED
#define DYNAMIC_PROGRAMMING_H_INCLUDED
#include <iostream>
#include <vector>

using namespace std;


/*动态规划5步
 *1.确定dp数组（dp table）以及下标的含义
 *2.确定递推公式
 *3.dp数组如何初始化
 *4.确定遍历顺序
 *5.举例推导dp数组
 */

//定义打印数组的函数
void printVector(vector<int> vec) {
    cout << "[" << vec[0];
    for (int i = 1; i < vec.size(); i++) {
        cout << ',' << vec[i];
    }
    cout << "]" << endl;
}

//定义打印二维数组的函数
void print2Vector(vector<vector<int>> result) {
    for (int i = 0; i < result.size(); i++) {
        printVector(result[i]);
    }
    cout << "-----------------------" << endl;
}

/*1 斐波那契数
 *1.1 确定dp数组 下标表示第i个菲波那切数，dp[i]表示第i个菲波那切数的值
 *1.2 确定递归公式 dp[i] = dp[i-1] + dp[i-2]
 *1.3 dp数组如何初始化 dp[0] = 0 dp[1] = 1
 *1.4 确定遍历顺序 从前往后遍历
 *1.5 举例推导dp公式 看看我们的dp公式是否正确合理
 */
int fib(int n) {
    if (n <= 1) return n;
    vector<int> dp(n+1);//定义具有n+1个元素的dp数组,因为下标为n的数其实是第n+1个，下标从0开始
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
        printVector(dp);
    }
    return dp[n];
}

/*2 爬楼梯
 *1.确定dp[i]数组 下标：到第i个阶梯 元素：到第i个阶梯有多少种方法
 *2.确定递推公式 dp[i] = dp[i-1] + dp[i-2]
 *  比如到了第i阶，可以从i-1到i,也可以从i-2到i,从i-1到i有dp[i-1]种方法，i-2到i有dp[i-2]种
 *  所以，到第i阶，共有dp[i] = dp[i-2] + dp[i-1]
 *3.dp数组如何初始化dp[1] = 1 dp[2] = 2 注意，这里讨论dp[0]没有意义，因为，不存在第0个台阶
 *4.确定遍历顺序 从前往后
 *5.举例推导dp公式
 */
int climbStairs(int n) {
    if (n <= 2) return n;
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

/*3 使用最小花费爬楼梯
 *1.确定dp数组 下标i:爬到了第i个阶梯   元素:dp[i]爬到第i个位置需要的最小花费(这个值是不包含cost[i]的)
 *2.确定地推公式 dp[i] = min(dp[i-1] + cost[i-1], dp[i-2]+cost[i-2])
 *3.初始化dp数组 dp[0] = 0 dp[1] = 0 题目中说，可以直接从0或者1开始跳，说明跳到0,1是不消耗体力的
 *4.确定遍历顺序 从前往后
 *5.手动模拟推导递归公式
 */
int minCostClimbingStairs(vector<int>& cost) {
        if (cost.size() <= 2) return 0;

        vector<int> dp(cost.size()+1);
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= cost.size(); i++) {
            dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
            printVector(dp);
        }
        return dp[cost.size()];//就是到的cost最后一个元素的后一个位置所需要的最小花费
}

/*4 不同路径
 *1.确定dp数组 dp[i][j]到达第i,j个位置，共有多少种路径
 *2.确定递归公式
    如果，一个位置，其上面有空位，且左边有空位，那么从[0,0]到这个元素的路径有
        dp[i][j] = dp[i-1] + dp[j-1] 因为机器人只能往左走，往下走
    如果，一个位置，只是上面有空格，那么从[0,0]到这个位置的路径有dp[i][j] = dp[i-1][j] = 1
    如果，一个位置，只是左边有空格，那么从[0,0]到这个位置的路径有dp[i][j] = dp[i][j-1] = 1
 *3.初始化递推公式 给最上边一行初始化为1，给最左边一列初始化为1
 *4.确定递推运行的方向 从左上到右下,只有把上边一行遍历完了， 才能遍历下面一行，
    因为，下边一行的计算要用到上边一行计算的结果。
 *5.模拟递推公式运行情况
 */
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n));//定义一个m行n列的二维数组
    //给dp[0][j]赋值, 给dp[i][0]赋值
    for (int j = 0; j < n; j++) dp[0][j] = 1;
    for (int i = 0; i < m; i++) dp[i][0] = 1;
    //逐行计算到每一行每个元素的路径条数
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
        print2Vector(dp);
    }
    return dp[m-1][n-1];
}

/*5 不同路径2
 *1.定义dp数组 dp[i][j] 就是从star到dp[i][j]一共有多少条路径
 *2.确定dp数组的递推公式
        最上一行dp[0][j] = 1,最左边一行dp[i][0]=1,如果上一行有障碍，那么障碍后面的dp元素都是0
        如果第0列有障碍，那么障碍下面的dp元素都是0
        如果左边有障碍，dp[i][j] = dp[i-1][j], 如果上边有障碍，dp[i][j] = dp[i][j-1]
 *3.初始化dp数组
 *4.遍历顺序 从上到下，从左到右
 *5.模拟递推公式的情况
 */
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    //定义dp数组
    vector<vector<int>> dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size()));
    //特殊情况，如果终点位置有阻碍，直接返回0
    if (obstacleGrid[obstacleGrid.size()-1][obstacleGrid[0].size()-1] == 1 ||
        obstacleGrid[0][0] == 1) return 0;
    //初始化dp数组,先初始化第一列，遇到阻碍，底下的dp要设置为0
    for (int i = 0; i < obstacleGrid.size(); i++) {
        if (obstacleGrid[i][0] == 1) {
            break;
        }else {
            dp[i][0] = 1;
        }
    }
    //初始化第一行，同样遇见阻碍，后面的dp元素要设置为0
    for (int i = 0; i < obstacleGrid[0].size(); i++) {
        if (obstacleGrid[0][i] == 1) {
            break;
        }else {
            dp[0][i] = 1;
        }
    }

    //开始递推
    for (int i = 1; i < obstacleGrid.size(); i++) {
        for (int j = 1; j < obstacleGrid[0].size(); j++) {
            if (obstacleGrid[i][j] == 1) continue;//使用continue，跳过，那么本质上这个位置的dp就是0了
            //阻碍位置的右边或者下边位置计算的时候，阻碍位置就会+0,相当于只加上了没有阻碍的那个元素
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
            /*
            if (obstacleGrid[i-1][j] == 1 && obstacleGrid[i][j-1] == 0) {
                dp[i][j] = dp[i][j-1];
            }else if (obstacleGrid[i-1][j] == 0 && obstacleGrid[i][j-1] == 1) {
                dp[i][j] = dp[i-1][j];
            }else if (obstacleGrid[i-1][j] == 1 && obstacleGrid[i][j-1] == 1) {
                dp[i][j] = 0;
            }else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }*/
        }
        print2Vector(dp);
    }
    return dp[obstacleGrid.size()-1][obstacleGrid[0].size()-1];
}

/*6 整数拆分
 *1.dp数组的含义:  dp[i] 拆分数字i，可以得到的最大拆分元素的乘积就是dp[i]
 *2.dp数组推导公式: 这里有两种拆分算乘积的方式，
    1.dp[i] = dp[i-j]*j
        这种方式，首先看看dp[i-j]是什么，是拆分数字i,可以得到的最大拆分元素的乘积
        其实就是将i 拆分成了i-j 和j,其中，i-j再拆分，算出i-j拆分元素的最大乘积，用这个乘积和剩下的一部分j相乘
        得到dp[i]的结果
    2.dp[i] = (i-j)*j
        这种方式，是直接将i拆分成两个部分，i-j 和 j，然后计算这两个数的乘积
    综合，递推公式：dp[i] = max(dp[i], max(j*dp[i-j], (i-j)*j)) //dp[i]数组默认是0的
 *3.初始化dp数组
    dp[0]和dp[1]没有意义，也没法拆分，所以，不用为了拆分而拆分
    直接初始化dp[2] = 1 dp[3] = 2
 *4.确定遍历顺序 从前往后
 *5.举例推导dp公式，看看dp公式是否合理
 */
int integerBreak(int n) {
    vector<int> dp(n + 1);
    //初始化dp数组
    dp[2] = 1;
    //遍历dp数组
    for (int i = 3; i <= n; i++) {
        for (int j = 1; j <= n/2; j++) {
            dp[i] = max(dp[i], max(j*dp[i-j], j*(i-j)));
        }
        printVector(dp);
    }
    return dp[n];
}

/*7 不同的二叉搜索树
 *1.确定dp数组的含义 dp[i] 1到i，i个结点组成的二叉搜索树的个数
 *2.确定dp数组的递推公式
    dp[i] += dp[j-1]*dp[i-j]其中j-1是以i为根左子树上结点的个数
    其中i-j是以i为根的结点，在右子树上的个数
 *3.初始化dp数组 dp[0] = 1
 *4.递归数组遍历的方向 由大到小
 *5.举例验证dp数组递推公式
 */
int numTrees(int n) {
    vector<int> dp(n+1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] += dp[j-1]*dp[i-j];
        }
        printVector(dp);
    }
    return dp[n];
}
#endif // DYNAMIC_PROGRAMMING_H_INCLUDED
