#ifndef BACKTRACKING_H_INCLUDED
#define BACKTRACKING_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

//1 组合问题
//定义result_01，用来储存最后的结构，这是一个二维数组，其中每一个元素都是一个一维数组
vector<vector<int>> result_01;
//定义path_01,这个数组中只维护k个元素，如果path_01中元素个数满足k个，就将当前path_01加入到result_01中
vector<int> path_01;
//为什么回溯里面的path也定义成全局变量？
//因为，是一直在对这个path做修改，然后把每次修改后满足条件的path的副本存入到result中。
//这个修改的过程，就是回溯的过程。每次回溯，都会弹出一个末尾元素，然后添加新的元素。
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


/*2 组合综合（三）
 *题目描述：
 *找到k个数字，这k个数字的和是n
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


/*3 电话号码的字母组合
 *题目描述：
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

/*4 组合总和
 *题目描述：
 *给定一个数组candidates和一个目标数字target
 *注意：candidates中的数在[2,40]之内,且均为正整数，且candidates中的元素不重复
 *要求：从candidates中挑选数字，让这些数字之和为target
 *对于candidates中的数字可以重复使用
 *比如：
 *输入: candidates = [2,3,5], target = 8
 *输出: [[2,2,2,2],[2,3,3],[3,5]]
 */
vector<vector<int>> result_04;//定义二维int数组，用来保存最终的结果
vector<int> path_03;//定义path_04用来保存每一个路径上的结果
void combinationSum(int sum, int target, vector<int> candidates, int startIndex) {
//step1：确定回溯算法的参数
//sum:记录当前path_03中所有元素的和
//target:这是path_03中元素的目标和
//startIndex:for循环开始的下标，为了防止组合重复
//这个题目对path中元素个数是没有要求了
//step2：回溯算法终止的条件
    //2.1 剪枝，当当前path_03中元素之和已经大于target时候，就停止
    //if (sum > target) return;
    //2.2 如果当前path_03中的数字之和为target,就把当前path加入到result_04中
    if (sum == target) {
        result_04.push_back(path_03);
        return;//这里返回上一层，因为，如果再加长path_04的元素个数，就会大于target了
    }
//step3：回溯算法的单层逻辑
    //注意：这里是i < candidates.size()不能写成<=，写成<=就越界了会出现candidates[candidates.size()]这种情况出现
    for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
    //每次都要对candidates从头开始遍历，因为，path_04中的元素可以重复出现
    //剪枝2.2：在剪枝1.1中判断了，如果sum大于target就继续进行了，这时候，其实已经多算了一次了
    //因为，如果没多算，不可能得到一个大于target的sum的，所以，我们这里就要优化，不然递归进入到
    //sum计算出来大于target的那一层。具体操作就是加上sum + candidates[i] <= target
    //这样，可以保证，for循环体里面，进入下一层递归的sum都是<=target的，如果大于target,就不会进入。
        sum += candidates[i];
        path_03.push_back(candidates[i]);
        combinationSum(sum, target, candidates, i);
        //这里是从i开始不是从i+1开始，因为元素可以重复出现
        //回溯
        sum -= candidates[i];
        path_03.pop_back();
    }
}

/*5 数组总和（二）
 *题目描述：
 *给定一个candidates和一个target
 *从candidates中挑出元素，使得挑出的元素之和为target
 *注意：
 *1.candidates中的元素可能重复，但是candadates中的元素不能重复使用
 *2.candidates中的元素都在[1,50]之内，且都为正整数，且可能重复
 */
vector<vector<int>> result_05;//定义result_05保存最后的结果
vector<int> path_05;//定义path_05用来保存路径上的元素
void combinationSum2(int target, int sum, int starIndex, const vector<int>& candidates, vector<bool>& used) {
    //step1：回溯算法的参数
        //used：标记已经使用过的元素
    //step2：回溯终止的条件
    if (sum == target) {
        result_05.push_back(path_05);
        return;
    }
    //step3：单层回溯的逻辑
    //starIndex控制下一层递归从哪里开始，后面的条件判断决定递归到哪里结束
    for (int i = starIndex; i < candidates.size() && sum + candidates[i] <= target; i++){
        /*去重：这个题目中，candidates中元素可以重复，path中的元素也可以重复，但是result中的元素不能重复
         *比如：candidates:[1,1,2]
         *可能出现[1,1], [1,2], [1,2]这几种情况，[1,2]重复了两次，而且这里的两个1是来自不同的1
         *这时候就要进行去重。在使用candidates的时候，要先对其进行排序，如果candidates[i]==candidates[i-1]的时候
         *说明，以candidates[i]开头的所有情况已经被candidates[i-1]开头所包含了，这时候continue就行了。
         */
        if (i > 0 && candidates[i] == candidates[i-1] && used[i-1] == false) {
            continue;//注意，这里要加上used[i-1]== fasle是为了防止[1,1,2]这种类型的path被跳过
        }
        sum += candidates[i];
        path_05.push_back(candidates[i]);
        used[i] = true;
        combinationSum2(target, sum, i+1, candidates, used);
        //回溯
        used[i] = false;
        sum -= candidates[i];
        path_05.pop_back();
    }
}

/*6 分割回文串
 *给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
 *返回 s 所有可能的分割方案。
 *示例: 输入: "aab" 输出: [ ["aa","b"], ["a","a","b"] ]
 *注意，这里的每一个path都是vector<string>类型的，是一个字符串类型的数组
 *即，每一个path就是一种对s的分割方式
 *问题，对于不能构成回文的path是怎么排除的？
 *做if判断，把只能构成回文的字符串加入，不能构成的不加入。
 *比如上面的例子：
 *for循环i指向0，从第一个a开始，a,可以构成加入path，进入下一层回溯，stratIndex从第二个a开始
 *第二个a可以构成加入path，进入下一层回溯，startIndex从b开始
 *b可以构成加入path,进入下一层回溯，判断starIndex==s.size(),将当前path加入result
 *当前path为["a", "a","b"]
 *回溯到上一层，弹出b,当前path为["a","a"]
 *回溯到上一层,弹出a,当前path为["a"]
 *回溯到上一层，弹出a,当前path为[]
 *此时，for循环i指向1,从第二个a开始
 *检测第一个子串切片为长度为1 - startIndex + 1 = 1 - 0 + 1 = 2
 *判断"aa"是否为回文，是，加入path
 *进入下一层递归，startIndex从b开始，判断b是回文，加入path=["aa", "b"],进入下一层递归，把当前path加入result
 *当前result为[["a", "a","b"],["aa", "b"]]
 *回溯到上一层，弹出b, 回溯到上一层，弹出aa,此时path为[]
 *此时，for循环i指向2，从b开始
 *检测管当前子串切片为3
 *判断aab是否为回文，不是，for循环结束。
 *最终result为[["a", "a","b"],["aa", "b"]]
 */
vector<vector<string>> result_06;
vector<string> path_06;
//声明回文检测函数
bool isPalindrome(const string&, int, int);
//定义回溯算法
void Partition(const string& s, int startIndex) {
    //回溯终止的条件
    //如果startIndex已经到了s字符串的最后一个位置，那么就可以将path加入了
    //因为starIndex已经不能再往后走了
    if (startIndex >= s.size()) {
        result_06.push_back(path_06);
        return;
    }
    //单层递归的逻辑，判断是否为回文的逻辑也在这里，只有是回文的字符串才会加入paht
    for (int i = startIndex; i < s.size(); i++){
        //判断是否为回文串
        if (isPalindrome(s, startIndex, i)){
            //获取[startIndex, i]在s中的子串
            //substr函数：是切分出s的一个子串，这个子串起始下标是第一个参数，子串的长度是第二个参数
            string str = s.substr(startIndex, i - startIndex + 1);
            //将切分好的子串加入到path中
            path_06.push_back(str);
        } else {
            //如果这个片段不能构成回文，那就跳过当前i的for训话，进入下一个i
            continue;
        }
        //递归进入下一层
        Partition(s, i + 1);//下一次切分就要从当前i的下一个位置开始了
        //每次递归到最后一层的时候，将会判断startIndex是否到最后一层了，
        //如果到了，就会将当前的path_06加入到result_06中去
        //所以，无论给定的s是一个怎样的字符串，都至少存才一个path
        //这个path中，每个元素是一个字符串s比如s = "abc"
        //result就是[["a", "b", "c"]]
        //回溯
        path_06.pop_back();//弹出子串，以寻找下一种切片组合
    }
}

//判断是否为回文（这里是判断字符串s的一个子串是否为回文）
bool isPalindrome(const string& s, int start, int End) {
    for (int i = start, j = End; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

/*7 复原IP地址
 *给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
 *有效的 IP 地址 正好由四个整数（每个整数位于0到255之间组成，且不能含有前导0），
 *整数之间用 '.' 分隔。
 *例如："0.1.2.201"和"192.168.1.1" 是有效的IP地址,但是"0.011.255.245""192.168.1.312"和
 *"192.168@1.1" 是 无效的 IP 地址。
 *示例 1：
 *输入：s = "25525511135"
 *输出：["255.255.11.135","255.255.111.35"]
 *示例 2：
 *输入：s = "0000"
 *输出：["0.0.0.0"]
 */
vector<string> result_07;
bool isValid(const string&,int,int);
void restoreIpAddresses(string& s, int startIndex, int pointNum) {
/*参数：pointNum表示添加逗点的数量
 */
/*思路：
 *本题，是要找出s符合条件的ip地址划分，不是在s中挑几个元素做排列组合
 *所以，不会改变s顺序，就不需要path了。直接对s进行划分添加逗号。
 *添加逗号后，将符合条件的s加入的result_07就可以了。不符合条件会回溯到上一层重新划分。
 *如果一直招不到合适的划分，就会返回空的result_07
 */
    //回溯算法终止条件：如果当s中的逗号数量到达了3说明前三个段已经判断合法
    if (pointNum == 3) {
        //判断第四个子字符串是否合法，如果合法就加入到result中
        if (isValid(s, startIndex, s.size() -1)) {
            result_07.push_back(s);
        }
        return;
    }

    //单层遍历的逻辑
    for (int i = startIndex; i < s.size(); i++) {
        if (isValid(s, startIndex, i)){
        //判断[startIndex,i]这个区间的子串是否合法
            s.insert(s.begin() + i + 1, '.');//在i后面添加一个逗点
            pointNum++;//添加完逗点pointNum就要加一
            restoreIpAddresses(s, i + 2, pointNum);
            //加入逗点后，下一个区间的起始位置为i+2,因为是左闭右闭区间的
            //回溯
            pointNum--;
            //erase函数：删除掉字符串s的指定位置的指定字符
            s.erase(s.begin() + i + 1);//回溯删除掉逗点
        } else break;//不过不合法，直接结束本层for循环
    }
}

//判断字符串s在左闭右闭的区间[start, end]所组成的数字是否合法
bool isValid(const string& s, int start, int End) {
    if (start > End) {
        return false;//如果这个区间是空区间，返回不合法
    }
    //这个区间如果超过一个字符，且首字符为空，则为不合法，即012这种区间
    if (s[start] == '0' && start != End) {
        //start!=false表示这个区间超过一个字符
        return false;
    }
    int num = 0;
    //判断s内是否有符号或者小于0的数字
    //如何判断是否不为数字：判断当前字符的ASCII码，如果在'0'到'9'之间就是合法的
    for (int i = start; i <= End; i++) {
        if (s[i] > '9' || s[i] < '0') {
            return false;
        }
        //在这个区间内，如果计算出来这个区间的最大值是大于255的不合法
        /*如何计算?
         *比如这个区间为"123"
         *先选取第一个元素"1"将其转换成数字"1"-"0" = 1
         *选取第二个元素"2",将第一个元素1*10加上"2"-"0" = 2,最后结果为12
         *选取第三个元素"3",将第二个元素算出来的结果12*10加上"3"-"0" = 3，最后结果为123
         */
        num = num * 10 + (s[i] - '0');
        if (num > 255) {
            //如果大于255了，则不合法
            return false;
        }
    }
    return true;
}

/*8 子集
 *给定一组不含重复元素的整数数组nums，返回该数组所有可能的子集
 *说明：解集不能包含重复的子集
 *示例：输入: nums = [1,2,3] 输出: [[3],[1],[2],[1,2,3],[1,3],[2,3],[1,2],[]]
 */
vector<vector<int>> result_08;
vector<int> path_08;

//定义回溯算法
void subsets(vector<int>& nums, int startIndex){
/*思路
 *空集是必然存在的，所以，可以把添加空集放在回溯算法之外添加。
 *对于叶子结点，非叶子结点的path都要加入到result中。
 *startIndex就要从i+1开始。
 *什么时候path可以加入result呢？
 *只要进入了下一层递归，都要加入
 */
    result_08.push_back(path_08);
    if (startIndex >= nums.size()) {
        return;
    }
    //单层递归的逻辑
    for (int i = startIndex; i < nums.size(); i++) {
        path_08.push_back(nums[i]);
        subsets(nums, i + 1);
        path_08.pop_back();
    }
}

/*9 子集二
 *给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 *说明：解集不能包含重复的子集。
 *示例:
 *输入: [1,2,2]
 *输出: [[2], [1], [1,2,2], [2,2], [1,2], []]
 */
vector<vector<int>> result_09;
vector<int> path_09;
void subsets2(vector<int>& nums, vector<bool>& used, int starIndex) {
    //每次遇到一个路径，都要放进去
    result_09.push_back(path_09);
    //单层回溯的逻辑
    for (int i = starIndex; i < nums.size(); i++) {
        //去重
        /*对nums进行去重，如果当前nums[i]和nums[i-1]相同，则跳过当前for循环
         *注意：nums= [1, 1, 2]最终的结果里面是有[1, 1,2]这种情况的
         *但是只能有一个[1,2]。所以要使用used数组，用来跳过第二个1和2组成的[1,2]
         *如果不用used数组，[1,1,2]这种情况也会被删除了。
         */
        if (i > 0 && nums[i] == nums[i-1] && used[i-1] == false){
            continue;
        }
        //否则，就加入到path中
        path_09.push_back(nums[i]);
        //将used位修改为true
        used[i] = true;
        subsets2(nums, used, i+1);
        //回溯
        used[i] = false;
        path_09.pop_back();
    }
}

/*10 递增子序列
 *给定一个整数数组，你的任务是找到所有该数组的递增子序列，递增子序列的长度至少是2。
 *示例:
 *输入: [4, 6, 7, 7]
 *输出: [[4,6],[4,7],[4,6,7],[4,6,7,7],[6,7],[6,7,7],[7,7],[4,7,7]]
 *说明:
 *给定数组的长度不会超过15。
 *数组中的整数范围是 [-100,100]。
 *给定数组中可能包含重复数字，相等的数字应该被视为递增的一种情况
 */
vector<vector<int>> result;
vector<int> path;
void findSubsequences(vector<int>& nums, int startIndex) {

}

#endif // BACKTRACKING_H_INCLUDED
