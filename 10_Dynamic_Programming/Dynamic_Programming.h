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

#endif // DYNAMIC_PROGRAMMING_H_INCLUDED
