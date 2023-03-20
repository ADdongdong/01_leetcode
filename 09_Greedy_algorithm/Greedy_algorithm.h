#ifndef GREEDY_ALGORITHM_H_INCLUDED
#define GREEDY_ALGORITHM_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

void print2Vector(vector<vector<int>> result) {
    cout << "[";
    //for (vector<int> i : result) {
    for (int i = 0; i < result.size(); i++){
        //如果遇到了空数组，就对其进行特殊处理，不然程序会终止
        if (result[i].size() == 0) {
            cout << "[]";
            continue;
        }
        if (i == 0) {
            cout << "[";
            cout << result[0][0];
            for (int j = 1 ; j < result[0].size(); j++){
                cout << ","<< result[0][j];
            }
            cout << "]";
            continue;
        }

        cout << ", [";
        cout << result[i][0];
        for (int j = 1; j < result[i].size(); j++) {
            cout << ","<< result[i][j];
        }
        cout << "]";
    }
    cout << "]" << endl;
}


/*1 分发饼干
 *假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
 *对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；
 *并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，
 *个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

 *示例 1:
 *输入: g = [1,2,3], s = [1,1]
 *输出: 1 解释:你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
 *             虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
 *             所以你应该输出1。
 *示例 2:
 *输入: g = [1,2], s = [1,2,3]
 *输出: 2
 *解释:你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
 *你拥有的饼干数量和尺寸都足以让所有孩子满足。所以你应该输出2.
 *
 *思路：
 *大饼干可以满足大胃口的孩子和小胃口的孩子，
 *小饼干只能满足小胃口的孩子。
 *所以，为了能让更多的小朋友被满足，所以，要让最大的饼干去满足胃口最大的孩子。
 *如果满足不了，就满足胃口次之的孩子，然后，依次类推。
 */
int findContentChildren(vector<int>& g, vector<int>& s) {
    //对孩子列表和饼干列表进行排序
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int num = 0;//定义num就是最大可以满足的孩子的数量
    //然后遍历饼干列表，如果s[i] > g[j] 那么就num+1，i++,j++，不然就j++
    int i = g.size()-1;
    int j = s.size()-1;
    while (i >= 0 && j >= 0){
        //这种写法可以发现，无论饼干是否满足当前孩子，孩子的下标都是要移动的
        //因此，可以以孩子下标为循环变量写出for循环
        if (s[j] >= g[i]){
            //如果当前饼干能满足当前孩子的胃口，那么就继续检查下一个饼干和下一个孩子
            num++;
            i--;
            j--;
        }else {
            //如果当前饼干不能满足当前孩子，说明当前孩子胃口太大，只能检查下一个孩子
            i--;
        }
    }
    /*另一种写法
    int index = s.size() -1;//定义饼干的下标
    int result = 0;//定义最终的结果
    for (int i = g.size() - 1; i >= 0; i--) {
        if (index >=0 && s[index] >= g[i]) {
            result++;
            index--;
        }
    }*/
    return num;
}

/*2 摆动序列
 *给定一个整数序列，返回:作为摆动序列的最长子序列的长度。
 *摆动序列是什么？
 *如果连续数字之间的差严格地在正数和负数之间交替，就称作摆动序列。第一个差可能是正数或负数。
 *如何获得一个序列的摆动序列？
 *通过删除或不删除原始序列中的一些元素，来获得子序列，使得这个子序列是摆动序列。

 *思路：
 *摆动序列有什么特点:a1>a2, a2<a3, a3>a4...数组元素的大小关系必须是大于小于交替出现的。
 *所以，对于给定的序列，要想让其称为摆动序列，就要避免出现连续的>或者<，也要避免出现=。
 *因此，我们在统计子序列长度的时候，如果有一个>，只需要往后找，找后面最近的一对<就行。
 *如果，只有一个>说明子序列长度为2，如果有个>还有个<说明子序列长度为3
 */
int wiggleMaxLength(vector<int>& nums) {
    //如果给定数组中元素只有一个，那么这就是最大的摆动序列
    if (nums.size() <= 1) return nums.size();
    int curDiff = 0;// 当前一对的差值
    int preDiff = 0;// 前一对差值
    int result = 1;// 记录峰值个数，序列默认序列最右边有一个峰值
    //以内循环体内是有i+1的，所以，i的上限就是nums.size()-1
    for (int i = 0; i < nums.size() - 1; i++) {
        curDiff = nums[i + 1] - nums[i];// 记录当前的差值
        // 出现峰值
        // 这里写成preDiff<=0其实，只有当nums只有两个结点的时候会触发等于号
        // 如果没有=那么两个结点的nums只会返回0
        // 如果一个nums = {1,2} 加上等于号，相当于给num前面加上了一个1
        // 这个=不会影响到后面的的元素的，因为curDiff >0 或curDiff <0 注意，这里都是没有等于号的
        // 并且，这个curDiff其实就是下一个cur的pre
        if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
            result++;
            preDiff = curDiff;// 只在摆出现变化的时候更新prediff
        }
    }
    return result;
}

/*3 最大子序和
 *给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
    示例:
 *输入: [-2,1,-3,4,-1,2,1,-5,4]
 *输出: 6
 *解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
 *
 *思路：
 *连续的子序列之和，对子序列的长度没有限制，就是最少得包含一个元素。
 *贪心算法采取局部最优化的策略。定义一个count记录当前连续自序列的总和，当这个总和小于0的时候，就抛弃当前count.
 *从i+1重新开始求新的子序列的和。
 *因为，如果，当前子序列和都为0了，无论后面那个数字有多大，加上负数都会变小。
 */
int maxSubArray(vector<int>& nums) {
    int result = INT32_MIN;
    int Count = 0;
    for (int i = 0; i < nums.size(); i++) {
        Count += nums[i];
        if (Count > result){
            result = Count;
        }
        if (Count < 0) {
            Count = 0;
        }
    }
    return result;
}

/*4 买卖股票的最佳时机二
 *给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 *设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
 *注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *示例 1:
 *输入: [7,1,5,3,6,4]
 *输出: 7
 *解释: 在第 2 天（股票价格 = 1）的时候买入，
 *在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4。
 *随后，在第 4 天（股票价格 = 3）的时候买入，
 *在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
 *思路:
 *要想股票最终收益最大，就要每个买卖都能挣到钱，也就是nums[i+1]-nums[i]>0，将这些区间加起来就行
 */
int maxProfit(vector<int>& prices) {
    int result =0;
    for (int i = 0; i < prices.size(); i++) {
        result += max(prices[i+1] - prices[i], 0);
    }
    return result;
}

/*5 跳跃游戏
 *给定一个数组，数组上的数字就是站在这个位置可以最多往前跳几步。
 *比如这里写3，就可以往前跳1,2,3步子。问的是，按照这个数组所给定的数字，能不能最终调到最后一个位置上去。
 *思路：
 *其实很简单，就看这个数组能覆盖的最大范围有没有包含到最后一个元素。
 *比如，数组长3，第一个格子就写了个5，那肯定没问题，能跳过去。就算5后面的所有格子都写0都能跳过去
 *所以核心在这个数组能覆盖的范围上。这个范围怎么算呢？
 *就是i + nums[i] >= nums.size() 就可以了。
 *注意，肯定会思考这样一种情况，比如跳到一个位置，再跳一个位置。
 *但是，其实本质上，这个"两连跳"的范围还是不会超过第二个元素上数组标注的位置。
 *如果第一次就可以跳很远，甚至，比第二次跳的最远距离还远，那能覆盖的范围还是第一次的范围。
 */
bool canJump(vector<int>& nums) {
    int cover = 0;//cover表示到当前元素未知，通过这些元素上的数字所能覆盖的数组长度
    //如果只有一个元素，那肯定能到达
    if (nums.size() == 1) return true;
    for (int i = 0; i <= cover; i++) {
        cover = max(i + nums[i], cover);//这里将最考前元素所能覆盖的最远范围和当前所能覆盖的范围做比较
        //并找到这两个范围中最大的那个范围，因为，这两个范围都是我们可以触达的，
        //只要最大的那个范围超过了nums.size()-1就够了，无论这个范围是从哪个元素跳过来的
        if (cover >= nums.size()-1){
            return true;
        }
    }
    return false;
}

/*6 跳跃游戏二
 *给定一个非负整数数组，你最初位于数组的第一个位置。
 *数组中的每个元素代表你在该位置可以跳跃的最大长度。
 *你的目标是使用最少的跳跃次数到达数组的最后一个位置。
 *注意：
 *这里，是使用最少的跳跃次数。上一个题目跳跃游戏中，不要求最少次数。
 *如何找到最小的跳跃？
 *先看第一个元素是否能满足，如果第一个元素就能满足，那就直接返回1。
 *如果第一个元素上数组包括的最大范围到不了列表的末尾，那就再第一个元素的范围内尝试。试试能不能跳两次到达范围。
 *先试，跳一步，然后从第二步能不能直接到达终点，依次类推...
 *什么时候增加跳跃次数？
 *当跳跃当前次数的所有组合都不能覆盖到末尾元素的时候，跳跃次数+1
 *比如：跳一次，就是从第一个元素开始，看看第一个元素覆盖的范围是否足够大，
        如果跳一次的最大范围不满足，不够大，那就跳跃次数+1,此时跳跃次数为2
        现在检查跳跃两次能够覆盖的最大范围。
        如果当前跳跃次数的某一个组合的最大范围达到或超过了列表，那就返回当前跳跃次数
 */
int jump(vector<int>& nums) {
    if (nums.size()==0)return 0;//如果当前列表长度为0，那就一次也不用跳
    int jumn = 0;//定义跳跃次数
    int curDistance = 0;//定义当前跳跃次数能覆盖的范围
    int nextDistance = 0;//下一步覆盖最远距离的下标
    for (int i = 0; i < nums.size(); i++) {
        nextDistance = max(nums[i] + i, nextDistance);//新的下一步最远下标
        if (i == curDistance) {
            if (curDistance < nums.size() -1) {
                jumn++;//跳跃次数+1
                curDistance = nextDistance;
                if (nextDistance >= nums.size() - 1) break;
            } else break;
        }
    }
    return jumn;
}

/*7 k次去反之后的最大和
 *题目解释：
 *给定一个数组nums, 给定一个次数k
 *要对nums中的元素进行去反，每次只对一个元素去反，并且，总共去反的次数之和为k次，可以对同一个元素多次取反
 *然后，求的是，怎样进行去反，用完k次，可以达到最大的数组之和。
 *思路：
 *先对Nums的绝对值进行排序，然后，从绝对值从大->小检查，又没有负数，如果有负数，先对这个负数去反一次，k--
 *并且，继续检查后面的元素，有没有负数，如果有继续去反。
 *总之，绝对值大的数字，如果有负数，有限对这些数字进行去反，如果全为正数，那么就对绝对值最小的元素反复去反，直到k次
 */
//定义比较器(比价容器是sort类中的静态函数，可以再类的外部定义)
static bool cmp(int a, int b) {
    return abs(a) > abs(b);
}
int largestSumAfterKNegations(vector<int>& nums, int k) {
    //对nums进行排序
    sort(nums.begin(), nums.end(), cmp);
    //从前往后遍历，如果出现了负号，则将其翻转并且k--
    for (int i = 0; i < nums.size(); i++){
        if (nums[i] < 0 && k > 0) {
            nums[i] = -nums[i];
            k--;
        }
    }

    //遍历完一圈nums,如果此时所有元素都是大于0，且k还不为0，那么就对绝对值最小的元素来回取反，知道k==0
    while (k > 0) {
        nums[nums.size() - 1] = -nums[nums.size() -1];
        k--;
    }
    //所有处理完以后，对整个数组进行求和
    int sum=0;
    for (int i = 0; i < nums.size(); i++){
        sum += nums[i];
    }
    return sum;
}

/*8 加油站
 *给定两个数组gas和cost
 *其中,gas数组中，每个元素指的是到这个站点，汽车可以获得多少汽油
 *cost指的是从i站到i+1站要消耗多少汽油。
 *题目问的是，从哪个站点开始出发，能保证过程中油是充足的，不会断油
 *思路：
 *贪心算法，从局部最优推到全局最优。
 *如果在所有站点加油的数量之和是小于消耗的汽油总和的，那么肯定找不出扎二个路径来。
 *反之，如果大于等于0，说明能找到一条路径让骑汽车不断油走完。
 *那么如果可以跑完，让对应的gas[i]-cost[i]求和，最终的结果也肯定是大于0的。
 *从0站开始，计算gas[i]-cost[i]的和，如果出现了到i的时候，这个和为0，说明路径得从i+1开始
 */
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int curSum = 0;
    int totalSum = 0;
    int start =0;
    for (int i = 0; i < gas.size(); i++) {
        curSum += gas[i] - cost[i];
        totalSum += gas[i] - cost[i];
        /*问题：为什么从0-i使用之差小于0，就要从i+1开始呢？
         *      从0-i之间一个位置开始不可能找到一条路径吗？
         *curSum<0有这么几种情况：
         *1.第0站油就不够用，从0-1加了1，消耗了2，那就从0+1开始
         *2.前面几站都能剩下油或油够用，突然，有一站，加油很少，费油很多。
         *  直接导致前面剩下的油都不够用了。那就必须从i+1开始找，因为，从0-i之间没有起始点了。
         *  如果从中间找，还是不够。
         *3.前面几站，攒了点油，但是，后面有几站都不够，把前面攒的用完了还不够。这样和2同理。
         *综上，无论如何，只要curSum<0了，都要从i+1开始，重新找路径，0-i中间是不可能的。
         */
        if (curSum < 0) {
            start = i+1;
            curSum = 0;
        }
    }

    if (totalSum <0) return -1;
    return start;//如果没有返回-1说明能找到一条路径，并返回这个路径的起始下标
}

/*9 分发糖果
 *n孩子站成一排（就是一个有n个元素的数组），老师要给这些孩子分发糖果，分发糖果要满足下面两个条件：
 *1、每个孩子至少一个糖果
 *2、相邻两个孩子，评分高必须获得更多的糖果（如果，评分相同，可以不获得更多的糖果）
 *问？如何让老师发出尽量少的糖果
 *思路：
 *1.对于第一个要求，我们可以直接生成一个全是1的candyVec，后面再这个列表上进行+操作，就能保证第一个条件了
 *2.对于第二个要求，我们对于每一个元素i,可以可以拆分为①ratings[i-1] < ratings[i]和②rating[i+1] < rating[i]
*   分别对上面两个条件做判断，如果满足①那就给i加1个糖果，如果满足②，那就将rating[i+1]+1和rating[i]做比较，选大的
 */
int candy(vector<int>& ratings) {
    vector<int> candyVec(ratings.size(), 1);//定义一个vector长度和打分表相同，所有元素均为1
    //从前向后遍历(相邻连个孩子，分数高的一定比分数低的孩子多获得糖果)
    for (int i = 1; i < ratings.size(); i++) {
        if (ratings[i] > ratings[i-1]) {
            //要保证比左边元素打一个，所以给右边元素赋值为左边的值+1,就一定比左边的大了
            candyVec[i] = candyVec[i-1] +1;//如果右边元素大于左边元素，那就给右边元素+1
        }
    }
    //从后向前
    for (int i = ratings.size() -2; i >= 0; i--) {
        //比较左边的元素和右边元素的大小，如果左边元素大于右边元素，那就++
        if (ratings[i] > ratings[i + 1]) {
            //如果，从前向后遍历的时候，i位置元素已经大于i+1位置元素，那就继续保持，
            //否则，就让其为i+1元素还大1的值
            candyVec[i] = max(candyVec[i], candyVec[i+1] + 1);
        }
    }
    //统计糖果总数
    int result;
    for (int i = 0; i < candyVec.size(); i++) result += candyVec[i];
    return result;
}

/*10 柠檬水找零
 *收入5，10,20
 *找零5 ，15
 */
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;//其实不要twenty也行
    for (int bill:bills) {
        //1.收入5元
        if (bill == 5){
            five++;
        }
        //2.收入10元
        if (bill == 10) {
            ten++;
            //如果有5元找零，否则，返回false
            if (five > 0) {
                five--;
            }else {return false;}
        }
        //3.收入20元，有限花10块的
        if (bill == 20) {
            if (ten > 0) {
                ten--;
                if (five > 0) {
                    five--;
                }else {return false;}
            }else if (ten ==0 && five > 2) {
                five -= 3;
            }else {
                return false;
            }
        }
    }
    return true;
 }

/*11 根据身高重建队列
 *描述：
 *假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。
 *每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面正好有ki个身高大于或等于hi的人。
 *要求：请你重新构造并返回输入数组 people 所表示的队列。
 *返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。
 *示例 1：
 *输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
 *输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
 *也就是说，要尽可能满足身高从高到低，同时必须满足[hj, kj]就是j前面有kj个身高大于等于hj的人
 *
 *思路：
 *先对其按照身高进行排序，排序完成以后，在按照j前又kj个身高大于等于hj的人排序，这样就可以尽可能满足这两个条件了。
 */
//定义对二维数组进行排序的比较器
static bool cmp_ (const vector<int>& a, const vector<int>& b) {
    //如果两个是同身高，那么，把同身高前面人少的放前面
    if (a[0] == b[0]) return a[1] < b[1];
    //如果两人不同身高，把个子高的放前面
    return a[0] > b[0];
}
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    //按定义的比较器对people按照身高进行从大到小排序
    sort(people.begin(), people.end(), cmp_);
    list<vector<int>> que;//定义队列，队列是链表类型的，因为链表的插入效率很高，vector查找效率很高，但是插入效率太低
    for (int i = 0; i < people.size(); i++) {
        int position = people[i][1];//插入到下标为position的位置
        //people的第二个元素指的是，这个人前面有大于[0]的几个人
        //因为，我们已经按照身高进行排序过了，所以，就不考虑[0]的值了
        list<vector<int>>::iterator it = que.begin();
        while (position--) {//寻找插入位置
            it++;
        }
        que.insert(it, people[i]);//在it位置插入people[i]
    }
    return vector<vector<int>>(que.begin(), que.end());
}

//12 使用最少数量的箭引爆气球
//定义sort函数的cmp参数，比较器
static bool cmp_12(const vector<int>& a, const vector<int>& b) {
    //按照气球半径的左端点进行排序
    return a[0] < b[0];//这样就是从小到大排序
}
int findMinArrowShots(vector<vector<int>>& points) {
    if (points.size() == 0) return 0;
    print2Vector(points);
    //对points列表进行排序
    sort(points.begin(), points.end(), cmp_12);
    print2Vector(points);

    int result = 1;//points 不为空至少需要一支箭
    for (int i = 1; i < points.size(); i++) {
        if (points[i][0] > points[i - 1][1]) {//这支箭的箭头和前一支箭的末尾没有重合，那就说明需要多一支箭。
            result++;
            cout << result << endl;
        }
        else {// 如果气球是挨着的，更新当前重复气球的最左边的最小右边界。
              // 因为，一旦下一个超过这个最小边界，就说明要多一支箭了
            points[i][1] = min(points[i - 1][1], points[i][1]);//更新重叠气球的最小右边界
            cout << points[i][1] << endl;
        }
    }
    return result;
}

/*13 无重叠区间
 *给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。
 *注意: 可以认为区间的终点总是大于它的起点。 区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。
 *示例 1:
 *输入: [ [1,2], [2,3], [3,4], [1,3] ]
 *输出: 1
 *解释: 移除 [1,3] 后，剩下的区间没有重叠。
 *注意，输出的是要移除的元素的数量，所以，对数组操作不用真的把真的元素移除，因为数组的插入和移除元素开销很大。
 */
//定义比较类
static bool cmp_13 (const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];//将这二维数组中的元素，按照开头从小到大进行排序
}
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    //如果这个二维数组为空，那么就说明不需要移除元素
    if (intervals.size() == 0) return 0;
    //对这个数组进行排序
    sort(intervals.begin(), intervals.end(), cmp_13);
    //定义end记录，当前没有重叠区间短的最小右值
    int End = intervals[0][1];
    int result = 0;
    for (int i = 1; i < intervals.size(); i++) {
        //如果当前元素的卡头小于上一个元素的结尾，那就说明重叠了，要移除
        if (intervals[i][0] < End) {
            result++;
            //移除以后，要给intervals重新赋值，因为，当移除了i,那么到i+1检测的时候，此时i+1对应的i就是i对应的i-1了
            End = min(End, intervals[i][1]);
        } else {
            //如果没有重叠，也要更新end
            End = intervals[i][1];
        }
    }
    return result;
}

/*14 划分字母区间
 *字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，
 *同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。
 *示例：
 *输入：S = "ababcbacadefegdehijhklij"
 *思路，遍历一遍整个字符串，找到每一个字符出现的区间
 *这个题目，既然让我们划分，说明，给出的字符串应该都是能划分的，
 *如果找到之前遍历过的所有字母的最远边界，
 *说明这个边界就是分割点了。此时前面出现过所有字母，最远也就到这个边界了。
 */
vector<int> patitionlabels(string S) {
    int hash[27] = {0};
    for (int i = 0; i < S.size(); i++) {
        //统计每一个字符最后出现的位置
        hash[S[i] - 'a'] = i;
    }
    vector<int> result;
    int left = 0;
    int right = 0;
    for (int i = 0; i < S.size(); i++) {
        //在for循环中，不断更新当前起始字符到现在遍历的第i个字符中，
        //所有字符出现的最远距离，因为这个距离前面已经计算出来了。
        //如果，此时i就是i以前所有元素的最远距离，那么，就可以丛这里划分了。
        right = max(right, hash[S[i] - 'a']);//找到字符串最远出现的点
        if (i == right) {
            result.push_back(right - left + 1);//计算区间长度
            //重启区间的开始点
            left = i + 1;
        }
    }
    return result;
}

/*15 合并区间
 *给出一个区间的集合，请合并所有重叠的区间。
 *示例:
 *输入: intervals = [[1,3],[2,6],[8,10],[15,18]]
 *输出: [[1,6],[8,10],[15,18]]
 *解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 *思路：还是以前面的【重叠区间】等题目为基础。首先，按照[0]从小到大对intervals进行排序
 *然后，进行比较。定义start,end变量，作为一个新的区间的结尾，如果重叠，就更新end。
 *如果不重叠，就将上个区间加入到result中，并开始一个新的区间更新start
 */
static bool cmp_15(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}
vector<vector<int>> Merge(vector<vector<int>>& intervals) {
    //定义result
    vector<vector<int>> result;
    //如果intervals为空，则返回0
    if (intervals.size() == 0) return result;
    //对intervals进行排序
    sort(intervals.begin(), intervals.end(), cmp_15);
    //定义区间的开始
    int star = intervals[0][0];
    //定义区间的结尾
    int End = intervals[0][1];
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] > End){
            //否则，当前区间和上一个去加不重叠，首先将上一个区间加入到result中
            result.push_back({star, End});
            //更新star和End的值
            star = intervals[i][0];
            End = intervals[i][1];
        } else {
            //如果当前遍历的区间，和上一个区间重叠，那么就把这个区间合并到上个区间内
            End = max(intervals[i][1], End);//选取最右边的边界作为新区间的右边界
        }
    }
    result.push_back({star, End});//将最后一个区间手动加入进来
    return result;
}
#endif // GREEDY_ALGORITHM_H_INCLUDED
