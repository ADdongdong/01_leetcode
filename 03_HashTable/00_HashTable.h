#ifndef _HASHTABLE_H_INCLUDED
#define _HASHTABLE_H_INCLUDED
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//1.有效的字母异位词
bool isAnagram(string s, string t){
//思路
//单词都是由26个字母组成的，所以，先把s这个单词映射在一个有26个元素的数组record上
//0->a ,15->z,
//step1：将字符串s映射到record上，s中的一个字母出现一次，将record中对应位置下+1
//step2：检查遍历字符串t，t中哪个字母出现一次，在record对应字母下-1
//step3：检查record，如果record数组都是0，则说明s和t构成字母异位的单词
    int record[26] = {0};
    for(int i = 0; i < s.size(); i++){
        record[s[i] - 'a']++;//该字母在record下对应的数字+1
    }
    for(int i = 0; i < t.size(); i++){
        record[t[i]-'a']--;//该字母在recored下对应的数字-1
    }
    //检查record数组
    for(int i = 0; i < 26; i++){
        if(record[i] != 0){
            return false;
        }
    }
    return true;
}

//2.两个数组的交集
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> result_set;//这个set来保存结果
    //所有向量和向量衍生容器都有迭代器，begin()函数会返回开始迭代器，
    //这个迭代器默认指向容器的首个元素
    unordered_set<int> nums_set(nums1.begin(), nums1.end());//用向量nums1生成一个set
    //其实可以理解为，多nums1中的元素去重，然后保存到nums_set中
    for (int num : nums2){//遍历nums2中的元素
        if(nums_set.find(num) != nums_set.end()) {
        //注意，这里nums_set.end()其实就可以理解为空NULL
        //也就是说，在nums_set中寻找nums2中的每一个元素
        //如果寻找的结果不是空。这就是if判断里面的意思。

        //如果，如果在nums1映射的集合nums_set中找到了
        //就把这个元素添加到result_set中。也就是求交集了。
            result_set.insert(num);
        }
    }
    return vector<int>(result_set.begin(), result_set.end());
}

//3.快乐数
int getSum(int n){
//这个函数用来计算十位上数字平方与个位上数字平法的和
    int sum = 0;
    //输入一个二位数，while会循环两次
    //第一次计算十位平方
    //第二次计算个位的平方
    //此时，n /= 10 的结果就是0了，while循环结束
    while(n){
        sum += (n%10)*(n%10);
        n /= 10;//34->3->0
    }
    return sum;
}

bool isHappy(int n){
//这个函数用来判断是不是happy number
//关键点：
//对于一个二位数来说，只有两种情况，要么是快乐数，要么不是快乐数
//是快乐数：不断计算，最后结果是1
//不是快乐数：不断计算，最后结果不是1,
//那什么情况下最后的结果不是1呢？
//那就是，计算可能陷入了死循环sum出现多次，当然，能出现2次，则必然会出现无数次
//如何判断一个数字是否重复出现呢？使用unordered_set
    unordered_set<int> set_record;//这个用来记录计算过程中sum出现过的数字
    while(1){
        int sum = getSum(n);
        if(sum == 1){
            return true;
        }
        if(set_record.find(sum) != set_record.end()){
        //如果此时计算出来的sum在set_record出现过，说明已经陷入循环了
            return false;
        }else{
        //如果此时的sum没有在set_record中出现过，则加入set_record，等待后面的检测
            set_record.insert(sum);
        }
        n = sum;//每次刷新n的值，不然永远都是false,哈哈
    }
}

//4.两数之和
vector<int> twoSum(vector<int>& nums, int target){
//题目描述：
/*给定一个整数数组nums和一个目标值target
 *请你在数组中找出和为目标值的那两个整数，
 *并返回他们的数组下标。（返回的值保存在一个数组中）
 *假设每种输入只会对应一个答案。
 *但是，数组中同一个元素在答案里不能重复出现
 */

//关键点：
//每种输入会对应一个答案，数组中同一个元素在答案中不能重复出现
//思路：
//遍历一个元素，将一个元素和其下标打包放在map中，元素值作为key,下标作为value
//这样可以保证，是正在遍历的元素和已经遍历过的元素做组合，保证了数组元素不重复出现
//而且，map中的元素值和下标值都保存成了pair所以，也方便获取下标
    unordered_map<int, int> _map;//建立一个空map,用来保存已经访问过的元素
    for (int i = 0;  i < nums.size(); i++){
        typedef typename unordered_map<int ,int>::iterator IT;//重命名map的迭代器
        //遍历当前元素，并在map中寻找是否有匹配的key
        IT iter = _map.find(target - nums[i]);//在map中找有没有能匹配上的元素
        if (iter != _map.end()){
            //如果匹配值能在map中找到，则返回这两个数的下标
            return {iter->second, i};//iter->second是map元素对应的value
            //i是当前遍历数组的下标
        }
        //如果没有找到匹配对，就把访问过的元素和下标加入到map中
        _map.insert(pair<int, int>(nums[i]/*key*/, i/*value*/));
    }
    return {};
}

//5.四个数字相加
int fourSumCount(vector<int> A, vector<int> B, vector<int> C, vector<int> D){
//描述:
/*A,B,C,D四个数组，计算有多少个(i,j,k,l)是的A[i] + B[i] + C[i] + D[i] = 0
 *所以这个题的返回值是int
 */
//思路:
/*这个题和上个题有相同的地方，先用map记录A,B数组中所有两数之和，和每种情况出现的次数
 *再遍历C,D数组，边遍历边在map中寻找0-(c+d)。
 *因为这个数字肯定已作为pair记录在map中了
 *每找到一组，就给count加上一个pair对应的value
 */

    unordered_map<int, int> umap;//创建一个map，来记录A和B所有元素之和可能出现的情况和出现的次数
    //遍历A,B两个数组，并统计所有元素之和和出现的次数
    for (int a : A){
        for (int b: B){
            umap[a + b]++;//这种添加map中键值对的方式和python字典是一样的
            /*
             *umap.insert(pair<int, int>(a+b, ??)
             *使用insert函数的话，value部分不好写实时更新
             *所以，用mapName[key]++这种方式来迭代key所对应value的值
             */
        }
    }
    //统计a+b+c+d = 0 出现的次数
    int _count = 0;
    // 再遍历C和D数组，如果找到 0-(c+d) 在map中出现过的话，
    // 就把map中key对应的value加到_count中
    for (int c : C){
        for (int d : D){
            if (umap.find(0 - (c+d)) != umap.end()) {
                _count += umap[0 - (c + d)];
                cout << "更新_count:" << _count << endl;
            }
        }
    }
    return _count;
}

//6
#endif // 00_HASHTABLE_H_INCLUDED
