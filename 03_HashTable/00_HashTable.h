#ifndef _HASHTABLE_H_INCLUDED
#define _HASHTABLE_H_INCLUDED
#include <iostream>
#include <vector>
#include <unordered_set>

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
#endif // 00_HASHTABLE_H_INCLUDED
