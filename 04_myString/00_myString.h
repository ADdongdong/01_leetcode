#ifndef _MYSTRING_H_INCLUDED
#define _MYSTRING_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//打印vector
template<class T>
void PrintVector(vector<T> v){
    for(auto a : v){
        cout << a << ' ';
    }
    cout << endl;
}

//1.翻转字符串
void reverseString(vector<char>& s){
//翻转字符串的本质就是翻转字符数组
    for(int i = 0; i < s.size()/2; i++){
        //两个指针指向的元素来回交换就行了
        char temp = s[i];
        s[i] = s[s.size()-1-i];
        s[s.size()-1-i] = temp;
    }
}

//2.翻转字符串II
string reverseStrII(string s, int k){
//描述
//给定一个字符串s和一个区间k
//丛s的开始到末尾，每次截取2k个元素，翻转前k个,后k个不变
//如果最后剩下的元素不足k个,则不翻转，如果剩下的元素超过k,则翻转前k个元素
//思路
//本来是for循环是i++,现在编程i += 2k,即每次向前走2k个，就直接到了下一个2k
//我们对这个2k做翻转就行了
    for (int i = 0; i < s.size(); i += (2*k)){
        //情况
        //1.i+k还在s内，则翻转i到i+k
        //2.i+2k已经超过了s的长度，i+k没有超过s长度，则翻转前i到i+k个
        if(i+k <= s.size()){
            reverse(s.begin() + i, s.begin() + i + k);//string 的reverse是包前不包后的，左闭右开
        } else {
            //3.剩余少于k个元素，全部翻转
            reverse(s.begin()+i, s.end());
        }
    }
    return s;
}

//3.替换空格
string replaceSpace(string s){
//描述
//把字符串s中的每个空格替换成"%20"
//思路
/*1.先把原来带空格的字符扩展成有%20字符的长度
 *2.从后往前将原来的字符串映射过来
 *注意，字符数组如果从前往后映射的话，就是o(n^2)了
 */
    //计算空格数量
    int kong_count = 0;
    int sOldSize = s.size();
    for (auto a : s){
        if(a == ' '){
            //注意:这里是+=2,为什么呢，没一个空格不是要换成三个字符吗？
            //因为，我们是要扩展原来的字符，所以原来的空格还在，也占一个字符。
            kong_count += 2;
        }
    }
    //将s的长度从s.size()扩展成s.size+kong_count
    s.resize(s.size() + kong_count);
    int newSize = s.size();
    //从前往后，用双指针法开始替换
    for (int i = newSize-1, j = sOldSize - 1; j < i; i--, j--){
        if(s[j] != ' '){
            s[i] = s[j];
        } else {
            s[i] = '0';
            s[i-1] = '2';
            s[i-2] = '%';
            i -= 2;
        }
    }
    return s;
}

//4.翻转字符串里的单词
void removeExtraSpace(string& s){
//描述，将一句话翻转
//比如，how are you!->you! are how
//注意：输入字符串的时候每个单词之间可能有多个空格，
//在完成翻转之后句子首位不能有空格，且，两个单词之间只能有一个空格
//思路：
//1.移除多余的空格
//2.两次翻转，<1>整个字符串整体翻转
//            <2>对每个单词再进行局部翻转
    //这个函数实现了去除多余的空格
    //多余空格可能出现在字符串前，中后
    //所以，还是使用快慢指针快指针i,只对非空格元素进行操作
    //即就是忽略对空格元素的操作，先给第一个非空格元素后面加上空格
    //表示每个单词后面都有一个空格然后，就一次让后面的元素依次往前移动到这个空格后面
    //直到出现下一个空格
    int slow = 0;//定义慢指针
    for (int i = 0; i < s.size(); i++){
        //只处理非空格字符
        if (s[i] != ' '){
            if(slow != 0) {
                s[slow++] = ' ';
            }
            //slow != 0 表示这不是第一个字符，对第0个位置上的字符不做操作，此时slow指向了第一个单词的后面一个位置
            //无论这个位置本来是不是空格，都给这个位置赋值为空格，然后再将slow的位置往后移动
            while (i < s.size() && s[i] != ' '){
                s[slow++] = s[i++];
            }
        }
        /*
         *   eg:"  hello world "
         *第一轮 s i
         *开始s->' ', i->'h', 只执行while，while结束时候，s指向'o'的后一个位置，i指向移动前'o'的后一个位置
         *
         *      "hello o world "
         *第二轮       s i
         *先指向if再指向while,
         *if：slow先将上一个单词后一个位置修改成空格，再往后一定一个单位指向新单词的开始
         *while：将第二个单词往前移动，结束的时候，slow的值就是下标值+1即为新的s.size()
         */
    }
    s.resize(slow);
}

//翻转字符串函数(使用锁闭右开的区间，和cpp自带的reverse保持一致)
void myReverse(string& s,int Start, int End){
    for (int i = Start, j = End-1; i < j; i++, j--)
        swap(s[i], s[j]);
}

string reverseWords(string& s) {
    cout << s << endl;
    removeExtraSpace(s);//首先对字符串进行去除多余空格处理
    cout << s << endl;
    myReverse(s, 0, s.size());
    cout << s << endl;
    int start = 0;//删除多余空格以后要保证第一个单词开始下标一定是0
    //遍历删除了多余空格的字符串，对立面的每个单词再进行翻转
    for (int i = 0; i <= s.size(); ++i) {
    //因为是用的左闭右开，所以末尾的i指针一定要能指向s.size()这个下标，不然，最后一个单词没法完全翻转
        //start来确定翻转单词的第一个下标，用来计算翻转单词最后一个字母的位置
        //到达空格或者串尾，说明一个单词结束，进行翻转操作
        if (i == s.size() || s[i] == ' ') {
            myReverse(s, start, i);
            start = i + 1;//更新start的位置
        }
    }
    cout << s << endl;
    return s;
}

//5.左旋转字符串
void leftMove(string& s, int target){
//描述：
//给定两个参数，字符串s和targer,就是把字符串的最前面两个元素移动到字符串最后面
//abcdefg -> cdefgab
//思路：
//将整个字符串s翻转
//翻转前s.size()-target个字符，翻转后target个字符
    //翻转整个字符串
    myReverse(s, 0, s.size());
    //翻转前s.size()-target个字符
    myReverse(s, 0, s.size()-target);
    //翻转后面target个字符
    myReverse(s, s.size()-target, s.size());
}

//6.KMP算法的实现
//定义函数构造next数组
void getNext(int* next, const string& s){
//这个函数是构造next数组,构造右移动之后的next数组
    //初始化
    //定义两个指针i和j，j指向前缀末尾位置，i指向后缀末尾位置
    //i指向后缀末尾，其实也就是当前子串的末尾
    //前缀是不包含最后一个字符，所有以第一个字符开头的子串
    //后缀是不包含第一个字符，所有以第一个字符结尾的子串
    int j = -1;
    next[0] = j;
    //i从1开始，因为只有一个字符的子串是没有前后缀的
    //有两个字符的自创，第一个字符就是前缀的开头，第二个字符就是后缀的结尾
    for (int i = 1; i < s.size(); i++){
        //处理前后缀不同的情况
        while (j >= 0 && s[i] != s[j+1]){
            j = next[j];
        }
        //处理前后缀相同的情况
        if (s[i] == s[j+1]){
            //找到相同的前后缀
            j++;
        }
        next[i] = j;//将j(前缀的长度)赋值给next[i]
    }
}

int strStr(string haystack, string needle) {
    if (needle.size() == 0) {
        return 0;
    }
    //定义next数组
    int next[needle.size()];
    //计算next的数组，第一个元素是-1，也就是右移动以后的
    getNext(next, needle);
    int j = -1;//因为next数组里记录的起始位置为-1
    for (int i = 0; i < haystack.size(); i++){
        while (j >= 0 && haystack[i] != needle[j + 1]){
            //不匹配的时候，就通过next数组，寻找前一个位置
            j = next[j];
        }
        if (haystack[i] == needle[j+1]){
            //如果匹配，i,j同时往后移动，检查后面的元素
            j++;
        }
        if (j == (needle.size() - 1)) {
            return (i - needle.size() + 1);
        }
    }
    return -1;
}

//7.重复的子字符串
bool repeatedSubstringPattern(string s) {
//描述：
//给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成
//给定的字符串只含有小写英文字母，并且长度不超过10000
//比如：abab 就可以由ab重复多次构成，aba就没有办法由其子串构成
    //用kmp想法解决
    if (s.size() == 0){
        return false;
    }
    int next[s.size()];
    getNext(next, s);
    int len = s.size();
    if (next[len - 1] != -1 && len % (len - (next[len - 1] + 1)) == 0) {
        return true;
    }
    return false;
}

#endif // 00_MYSTRING_H_INCLUDED
