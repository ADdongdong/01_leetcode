#ifndef DYNAMIC_PROGRAMMING_H_INCLUDED
#define DYNAMIC_PROGRAMMING_H_INCLUDED
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;


/*动态规划5步
 *1.确定dp数组（dp table）以及下标的含义
 *2.确定递推公式
 *3.dp数组如何初始化
 *4.确定遍历顺序
 *5.举例推导dp数组
 */

//定义打印数组的函数
template<class T>
void printVector(vector<T> vec) {
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
 *递推公式举例：
 *首先再明确一下dp数组的含义dp[j]表示，装满容量为j的背包，有多少种方法
 *那么我们来举例看看dp[5]是怎么来的：
 *假设nums[i]中还有一个1，那么有dp[4]种方法凑成容量为5的背包。dp[4]是装满容量为4的背包的方法数。
 *假设nums[i]中还有一个2，那么有dp[3]种方法凑成容量为5的背包
 *假设nums[i]中还有一个3，那么有dp[2]种方法凑成容量为5的背包
 *假设nums[i]中还有一个4，那么有dp[1]种方法凑成容量为5的背包
 *假设nums[i]中还有一个5，那么有dp[0]种方法凑成容量为5的背包
 *
 *dp[j] += dp[j - nums[i]]
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
            cout << "[i, j]:" << i << "," << j << endl;
            printVector(dp);
            cout << endl;
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

//12 零钱兑换
/*
 *给定不同面额的硬币coins和一个总金额amount.
 *编写一个函数来计算可以凑成总金额所需要的最少的硬币个数。
 *如果没有任何一种硬币组合能组成总金额。返回-1.
 *1.dp[j]数组的含义 凑成金额为j的硬币组合数为dp[j]种类
 *2.确定递推公式 dp[j] = min(dp[j - coins[i]] + 1, dp[j])
 *  解释：j是要凑够j块钱，j-coins[i]是要凑够j-coins[i]块钱
         dp[j - coins[i]]是要凑够j-coins[i]块钱至少需要的硬币个数
         那要凑够j块钱，只要在j-coins[i]块钱的基础上再加一个
         面值为coins[i]的硬币，就是dp[j]凑够j块钱要的最少硬币了。

 *3.dp数组如何初始化dp：dp[0]肯定是0，其他值都要初始化为最大值
 *4.遍历顺序
 *
 */
int coinChange(vector<int>& coins, int amount){
    //初始化dp数组
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    //遍历循环
    //遍历coins列表，从头开始遍历,比如coins第一个元素是1
    //那么里面的for循环就带边，只用1这一种硬币，要凑成1-amount
    //分别最少需要多少个硬币。
    //当遍历到coins的第二个元素2,
    //哪里里面的for循环就是，用面值为1和面值为2的硬币，凑成1-amount
    //分别最少需要多少个硬币。
    //比如，当只有硬币1的时候，凑成3需要三个硬币，即是3个1元硬币。
    //      当有1元硬币和2元硬币的时候，凑成3则最少需要两个硬币，即一个1元，1个二元。
    //这里的更新就是dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
    for (int i = 0; i < coins.size(); i++){
        //j从当前硬币的面值开始遍历，直到目标总钱数停止
        for (int j = coins[i]; j <= amount; j++){
            printVector(dp);//打印dp数组，看dp数组是如何更新的
            //dp[j-coins[i]]是我们更新dp[j]时候要用到的，所以要保证这个内容已经被更新过了
            //dp[j-coins[i]]就没有添加硬币coins[i]时候，最少需要几个硬币，如果这一项没有被更新，就无法比较
            cout << "dp[j -coins[i]]:" << dp[j - coins[i]] << endl;
            //if ( dp[j - coins[i]] != INT_MAX) {
                //更新dp[j],注意，这里是和dp[j]做比较，适合上一轮这个位置作比较
                dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
            //}
        }
    }
    if (dp[amount] == INT_MAX) return -1;
    return dp[amount];
}

//12 完全平方数
/*描述：
 *给定正整数n,找到若干个完全平方数（比如1,4,9,16，...）
 *使得它们的和等于n.你需要让组成和完全平方的个数最少
 *给你一个整数n,返回和为n的完全平方数的最少数量。
 *示例：
 *输入：n = 12
 *输出：3
 *解释：12 = 4+4+4
 *
 *转换：
 *这里的n相当于背包的容量，也是背包内容的价值。
 *这里的完全平方数相当于可以无限重复使用的物品。
 *问的是：凑够这个背包最少需要几个物品（这些物品必须都得是完全平方数）
 *
 * 递归五部曲
 *1.确定dp数组 dp[j] 和为j的完全平方数的最少数量为dp[j]
 *2.确定递推数组 dp[j] = min(dp[j - i*i] + 1, dp[j])
 *3.dp数组初始化 dp[0]=0,其他都是最大的
 *4.确定遍历顺序 本次知识求最小的数量，无关排列组合
 *5.推导 
 */
int numSquares(int n){
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    //开始遍历
    //这是先遍历背包，再遍历物品的代码
    for (int j = 0; j <= n; j++){
        for (int i = 1; i*i <= j; i++){
            dp[j] = min(dp[j - i*i] + 1, dp[j]);
            printVector(dp);
        }
    }
    /*下面是先遍历物品，在遍历背包的代码
    for (int i = 0; i*i <= n; i++) {
        for (int j = i*i; j <= n; j++) {
            //这里j要从i*i开始，因为当前物品的大小为i*i,所以要保证背包的容量大于i*i才能放下这个物品
            //也就是说，d[j - i*i]不能越界
            dp[j] = min(dp[j - i*i] + 1, dp[j]);
        }
    }
    
    */
    return dp[n];
}

//13 单词拆分
/*
 *给定一个费控字符串s和一个包含非空单词的列表wordDict,
 *判定s是否可以被空格拆分为一个或多个在字典wordDict中出现的单词。
 *注意：拆分时，可以重复使用字典中的单词。
 *举例：
 *s = "leetcode", wordDict = ["leet", "code"]
 *输出：true
 *解释：返回true,因为，字符串s可由被空格拆分成字典里有的单词。
 *如何将这个题目和背包问题对应起来？
 *字符串：背包
 *字典：物品
 *物品可以重复使用，只要能把背包放满，就算成功。
 *动态规划5步：
 *1.定义dp数组：dp[i]字符串长度为i的话，dp[i]为true，
 *表示可以拆分为一个或多个在字典中出现的单词
 *2.确定递推公式：如果确定dp[j]是true,且[j,i]这个区间的子串出现在字典里，
 *  那么dp[i]一定是true
 *  if([j, i]这个区间的子串出现在字典里 && dp[j]是ture) 那么 dp[i]=true
 *3.初始化字符串
 *  dp[0] = true dp[其他] = flase
 *4.确定遍历顺序
 *  先遍历背包，再遍历物品，因为对子串的顺序是有要求的
 *5.
 * 
 */
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    for(int i = 1; i <= s.size(); i++) { //遍历背包
        for (int j = 0; j < i; j++) { //遍历物品
            string word =s.substr(j, i -j); //substr函数,取s字符串的子串
            //substr(起始位置，截取字符个数)
            if (wordSet.find(word) != wordSet.end() && dp[j]) {
                dp[i] =true;
            }
            printVector<bool>(dp);
        }
    }
    return dp[s.size()];
}

#endif // DYNAMIC_PROGRAMMING_H_INCLUDED
