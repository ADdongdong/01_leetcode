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




#endif // DYNAMIC_PROGRAMMING_H_INCLUDED
