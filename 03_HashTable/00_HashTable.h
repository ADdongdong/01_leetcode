#ifndef _HASHTABLE_H_INCLUDED
#define _HASHTABLE_H_INCLUDED
#include <iostream>
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


#endif // 00_HASHTABLE_H_INCLUDED
