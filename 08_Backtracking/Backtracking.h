#ifndef BACKTRACKING_H_INCLUDED
#define BACKTRACKING_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//1 组合问题
//定义result_01，用来储存最后的结构，这是一个二维数组，其中每一个元素都是一个一维数组
vector<vector<int>> result_01;
//定义path_01,这个数组中只维护k个元素，如果path_01中元素个数满足k个，就将当前path_01加入到result_01中
vector<int> path_01;
void backtrackCombination(int n, int k, int starIndex) {
    //1.1 返回值：无返回值，
    //1.2 参数，当前是找[1, n]中元素的组合，所以，要给出这个范围
    //    参数k，一个组合中要有几个元素
    //    参数starIndex 表示当前递归从哪里开始
    //2 递归终止的条件
    if (path_01.size() == k) {
        //如果当前path_01的长度已经满足的组合k的长度
        //那就将当前path_01加入到result_01中
        result_01.push_back(path_01);
        return;//返回上一层递归
    }
    //3.单层递归的逻辑
    for (int i = starIndex; i <= n; i++) {
    /*优化：
     *for (int i = starIndex; i <= n- (k - path.size()) + 1; i ++)
     *如果当前数组剩下的元素，加上已经加入到path的元素已经不足k个元素了，就不在继续寻找了
     *如果当前数组剩下的元素加上已经加入到path的元素还大于k个元素，说明还有别的情况，继续寻找
     */
        //单层遍历，从starIndex开始，到n结束，注意，这里是包括n的，所以要加上等于号
        path_01.push_back(i);//将这个元素加入到path_01中
        //继续进行递归遍历，往当前path_01中添加元素
        backtrackCombination(n, k, i + 1);//下次起始元素就是这个元素的下一个位置了
        //遍历完以后，要进行回溯
        path_01.pop_back();
    }
}


//2 组合综合（三）
//题目描述：
/*找到k个数字，这k个数字的和是n
 *要求：
 *  这k个数字只能从1-9这9个正数中间选择
 *  组合不能重复出现比如有了[1,3]就不能再出现[3,1]
 */
vector<vector<int>> result_02;//定义二维数组result_02来存放最终的结果集合
vector<int> path_02; //定义一维数组path_02用来存放每个小的组合
void combinationSum3(int targetSum, int k, int sum, int startIndex) {
    /*targetSum: 目标和，就是题目中的n
     *k:  题目中要求的k个数字之和是，这个k就是组成n数字的个数
     *sum:已经收集到的元素的综合，也就是当前path_02中元素之和，
          用来判断当前path_02是否可以进入result_02
     *startIndex:下一层递归for循环开始的元素
     */

     /*可以从两个方面进行算法的优化
     *1.通过不断深层迭代，path_02中元素的和只会越来越大，
        如果，当前path_02的值已经大于targetSum了，就不用继续深层递归了，直接返回就行了
      2.如果剩余的元素个数，加上当前已经在path_02中的元素个数还不足k个的话，那就不用再继续了
        因为，再继续，也不会满足条件的
     */
     //算法优化：如果当前path_02中的元素个数已经大于所要求的k个了，那就可以直接返回上一层了
     if (path_02.size() > k) {
        return;
     }

     //step1：先递判断当前递归是否可以进入到result_02中
     if (path_02.size() == k) {
     //先判断path_02中元素的个数是否已经到达上限
        if (sum == targetSum) result_02.push_back(path_02);
        //在判断当前path_01中的元素之和是否为targetSum，如果是就把当前path加入到result中
        return;//如果再继续往下一层递归，不会再有满足条件的paht了,所以往上一层返回
     }

     //step2：单层递归
     for (int i = startIndex;i <= 9 - (k - path_02.size()) + 1; i++) {
        /*path.size() 是当前path中已经有的元素个数
         *k - path.size() 是要行程满足条件的k个元素的path,当前path还差几个元素
         *9 - i 是可选列表中还省下几个可选元素，比如，当前i是5，那么还有9-5=4个元素可选
         *如果可选元素个数 小于 满足k个元素还差的元素个数 那就不能继续了
         *反言之
         *如果可选元素个数 大于 满足k个元素还差的元素个数 那就继续进行递归
         *即就是
         *9 - i >= k -path.size()
         *即就是
         *9 - ( k- path.size()) >= i
         */
        sum += i;//将i加入到sum
        path_02.push_back(i);//将i加入到path_02
        combinationSum3(targetSum, k, sum, i + 1);//这里前两个参数都不变，sum在前面两行已经改变了
        sum -= i;//当前i对应的路径找完了，回溯到上一层，找下一个对应的路径，
        //每回溯一层，就要把在当前层加上的i从sum中和path_02中去除了
        path_02.pop_back();//回溯到上一层
     }
}


//3 电话号码的字母组合
/*题目描述：
 *手机的九宫格按键,2-9这几个数字上是有字母的
 *问，这几个数字，任意输出几个数字，有多少种组合方式
 * 比如：输入2,3
 * 可以有：ad, ae, af, bd, be, bf, cd, ce, cf
 *同样，如果输入更多的数组，那么组合的形式会更多
 */

//将2-9这8个数字对应的字符串映射到一个二维数组上
const string letterMap[10] = {
    "",//0代表空字符串
    "",//1代表空字符串
    "abc",//2
    "def",//3
    "ghi",//4
    "jkl",//5
    "mno",//6
    "pqrs",//7
    "tuv",//8
    "wxyz",//9
};

vector<string> result_03;//定义string类型的vector,result_03中的每一个元素都是string类型的
string s;//定义s，相当于前两个题的path，用来保存每一个小的组合，这些组合将会被添加到result_03上
void letterCombinations(const string& digits, int index) {
//step1:确定回溯算法的参数
//digits参数：按了那几个键，比如：23,2333,34...
//index参数：index记录遍历到了digits的那一个数字了

    //step2:确定终止条件
    //根节点为第0层，如果输入了两个数字：23，那么遍历到第二层的时候，就可以返回了
    if (index == digits.size()) {
        result_03.push_back(s);//如果检测到当前已经遍历到了第二个数字，就将s加入到result中
        return;
    }

    //step3：确定单层遍历的逻辑
    //3.1 找到index所指向的数字
    int digit = digits[index] - '0';//取出对应的字符，这个字符和0之间的差值，可以再letterMap中取字符串
    //比如，index为0，取到了'2'这个字符，'2'-'0' = 2,最后的这个结果2是int类型的
    string letter = letterMap[digit];//取letterMap中数字对应的字符串
    for (int i = 0; i < letter.size(); i++) {
        s.push_back(letter[i]);//取到2对应letterMap中字符串的第i个元素
        letterCombinations(digits, index + 1);//该遍历输入的第二个数字了，要从第二个数字中取字母了
        s.pop_back();//回溯到上一层
    }

}






#endif // BACKTRACKING_H_INCLUDED
