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

/*8 分割等和子集
 *用0-1背包解决这个题
 *1.背包的体积为sum/2
 *2.背包要放入的商品重量为元素的数值，价值也为元素的数值
 *3.如果背包正好装满了，说明找到了总和为sum/2的子集
 *4.背包中每一个元素是不可重复放入
 */
bool canPartition(vector<int>& nums) {
    int sum = 0;
    // dp[i]中的i表示背包内总和
    // 题目中说，每个数组中元素不会超过100， 数组大小不会超过200
    // 总和不会大于20000，背包最大只需要其中的一半，所以，只要有10001大小就行了
    vector<int> dp(10001, 0);
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
    }//计算nums的总和
    if (sum % 2 == 1) return false;//如果不能均分，总和为奇数，直接返回false
    int target = sum/2;

    //开始0-1背包
    for (int i = 0; i < nums.size(); i++) {
        for (int j = target; j >= nums[i]; j--) {
            dp[i] = max(dp[i], dp[j - nums[i]] + nums[i]);
        }
        printVector(dp);
    }
    //集合中的元素正好可以凑成总和target
    if (dp[target] == target) return true;
    return false;
}

/*9 最后一块石头的重量二
 */
int lastStoneWeightII(vector<int>& stones) {
    //定义dp数组
    vector<int> dp(15, 0);
    //计算sum
    int sum = 0;
    for (int i = 0; i< stones.size(); i++) {
        sum += stones[i];
    }
    //计算target
    int target = sum/2;
    cout << "target:" << target <<endl;
    //进行背包
    for (int i = 0; i < stones.size(); i++) {
        for (int j = target; j >= stones[i]; j--) {
            dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
        }
        printVector(dp);
    }
    int result = sum - dp[target] - dp[target];
    return result;
}

//10 目标和
/*给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
 *返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
 *示例：
 *输入：nums: [1, 1, 1, 1, 1], S: 3
 *输出：5
 *
 *思路
 *将nums分成两堆数据，让两堆数据的差为S就可以了
 *left - right = target
 *left + right = sum
 *right = sum - left
 *left - (sum - left) = target
 *left = (target+sum)/2
 *所以，我们的目标就是要在nums中找到和为left的组合
 *
 *step1.定义dp数组 dp[j]表示，装满j这么大的背包，有多少种方法
 *step2.dp数组递推公式dp[j] += dp[j - nums[i]]
 *step3.dp数组初始化 dp[0] = 1
 */
int findTargetSumWays(vector<int>& nums, int target) {
    //计算sum的值
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) sum += nums[i];
    //如果target的绝对值大于sum，则返回0，说明不可能凑成
    if (abs(target) > sum) return 0;
    //如果target+sum为奇数，则么有方案(left = (target+sum)/2)
    if ((target + sum) % 2 == 1) return 0;
    //定义dp数组
    int bagsize = (target + sum)/2;
    vector<int> dp(bagsize+1, 0);
    //初始化dp数组
    dp[0] = 1;
    //开始01背包
    for (int i = 0; i < nums.size(); i++) {
        for (int j = bagsize; j >= nums[i]; j--) {
            dp[j] += dp[j - nums[i]];
        }
    }
    return dp[bagsize];
}

/*11 一和零
 *1.确定dp数组的下标和含义
 *  dp[i][j] 最多有i个0和j个1的strs的最大子集大小为dp[i][j]
 *2.确定递推公式
 *  dp[i][j] 可以由前一个strs里的字符串推导出来，strs里的字符串有zeroNum个0，oneNum个1
 *  dp[i-zeroNum][j-oneNum]+1
    dp[i][j] = max(dp[i][j], dp[j - weight[i]] + value[i])
 */
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int> (n+1, 0));
    for (string str:strs) {
        int oneNum = 0, zeroNum = 0;
        for (char c : str) {
            if (c == '0') zeroNum++;
            else oneNum++;
        }
        for (int i = m; i >= zeroNum; i--) {
            for (int j = n; j >= oneNum; j--) {
                dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
            }
        }
        print2Vector(dp);
    }
    return dp[m][n];
}

#endif // DYNAMIC_PROGRAMMING_H_INCLUDED
