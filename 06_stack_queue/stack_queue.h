#ifndef STACK_QUEUE_H_INCLUDED
#define STACK_QUEUE_H_INCLUDED
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <unordered_map>
//#include <priority_queue>

using namespace std;

//1.用栈来模拟队列
class MyQueue {
public:
    stack<int> stIn;//定义输入栈，输入的数据都放在这个栈中
    stack<int> stOut;//定义输入栈，要输输出的数据都从stIn中移动到stOut中
    MyQueue() {

    }

    //1.向队列添加元素
    void push(int x) {
    //MyQueue是由两个栈来模拟的，所以，添加元素就是向stIn中push元素
        stIn.push(x);
    }

    //2.从队头删除元素
    //(队列是从队尾进入，从队头出)
    int pop() {
    //因为stIn的删除的是最近放入的元素，所以，要将stIn中的元素
    //放入到stOut中，再从stOut中出元素，这样才能保证是队列的出队顺序
        if (stOut.empty()) {
            //将stIn中的所有元素都移动到stOut中
            while (!stIn.empty()) {
                stOut.push(stIn.top());//将stIn中的数据移动到stOut中
                stIn.pop();//每移动一个stIn中的元素，就删除一个
            }
        }
        int result = stOut.top();//获取stOut的栈顶元素
        stOut.pop();
        return result;
    }

    //3.返回队列首部元素（队头元素）
    int peek() {
        int res = this->pop();//调用刚才定义的pop函数
        stOut.push(res);//因为刚才删除了res元素，所以要把这个元素再天剑进去
        //因为peek只是获取元素，不是删除元素
        //int res = stOut.top();不能这样使用，因为我们不知道stOut里面有没有元素
        //这个元素可能还在stIn中，所以不能这样来获取，必须通过pop函数的元素移动过程才能获取
        //stOut.push也不能写成this->push我们不是往stIn中添加元素
        //而是把刚才从stOut中弹出的元素再放进去
        return res;
    }

    bool isempty() {
        return stIn.empty() && stOut.empty();
    }
};

//2.用队列实现栈
class MyStack {
public:
    //1.定义一个队列
    queue<int> que;

    MyStack(){}//构造函数

    //1.往MyStack中添加元素
    void push(int x) {
        que.push(x);
    }

    //2.删除MyStach的栈顶元素
    int pop() {
        //如何获取栈顶元素呢？
        //队列中，最后一个进队的在对尾，最后出队
        //在栈中，最后一个入栈的，在栈顶，最先出栈
        //一次将队列对尾前的元素天剑到对尾的后面，
        //然后再进行出队，这时候，原来的队尾元素就到队头了
        int _size = que.size() - 1;
        while (_size--) {
            que.push(que.front());//获取队头元素，并加到
            que.pop();//stl中的queue的pop返回值为void
        }
        int result = que.front();//再获取队头元素，就是原来最后进队的元素了
        que.pop();
        return result;
    }

    //3.获取MyStack的栈顶元素
    int top() {
        return que.back();//直接返回队尾元素就行
    }

    //4.判断队列是否为空队
    bool isempty() {
        return que.empty();
    }

};

//3.有效括号
bool isValid(string s) {
//描述
//给定一个只包括[],{},()的字符串，判断字符串是否有效
//什么是有效，就是括号顺序能匹配上，数量能匹配上，
//三种情况被认为是没有匹配成功的
/*
1.左侧有多余的括号，这种情况再完成检测以后，栈能会有剩余的字符
2.有括号不匹配的情况，比如此时需要一个}，但是进来一个]这样就算是匹配失败
3.右侧有括号多余了，这种情况同样完成检测以后，栈内有剩余的字符
*/
//那代码如何实现匹配呢？
/*
每个元素挨个扫描，如果扫描到了开口向右的括号{[(这三种的，
则把它们渴望匹配的括号放入，比如扫描到了二{则把}放入栈。
如果扫描到了开口向左的括号，则看看栈顶的括号是否和这个括号相同。
相同则pop，不同则返回false
最后，再检查栈是否为空，栈若不空，则说明匹配失败
*/
    //如果字符串长为奇数，返回false
    if (s.size() %2 != 0) return false;
    stack<char> st;//定义栈
    for (int i = 0; i < s.size(); i++) {
        if(s[i] == '{') st.push('}');
        else if(s[i] == '[') st.push(']');
        else if(s[i] == '(') st.push(')');
        else if(s[i] != st.top() || st.empty()) return false;
        else st.pop();
    }
    return st.empty();
}

//4.删除字符串重复的元素
string removeDuplicates(string s) {
//描述：
//迭代删除字符串中重复的相邻字符
//啥意思呢，什么是迭代呢？就像这样abbac->aac->c
//思路
//使用栈，每次检查到一个元素，先和栈顶元素左比较，如果相同，则pop
//如果不同，则入栈吗。整个字符串扫描完毕，结束，所有元素出栈，然后再reverse就是最终的结果了
    stack<char> st;//定义一个stack
    for (char a : s) {
        //若当前检查到的元素和栈顶元素不同，或者为空栈，则这个元素入栈
        if (a != st.top() || st.empty()) {st.push(a);}
        else{
            //否则出栈
            st.pop();
        }
    }
    //所有元素出栈
    string new_s = "";
    while ( !st.empty()) {
        new_s += st.top();//字符串拼接
        st.pop();
    }
    reverse (new_s.begin(), new_s.end());
    return new_s;
}

//5.逆向波兰表达式求值（后缀表达式求值）
int evalRPN(vector<string>& tokens) {
//给一个后缀表达式，通过这个后缀表达式计算最终的式子的结果
//思路：
/*
如果遇到数字进栈，如果遇到符号，弹出栈顶两个元素，跟这个符号做运算，然后结果再进栈
*/
    stack<long long> st;
    for (int i = 0; i < tokens.size(); i++) {
        //如果遇到符号，就弹出栈顶相邻两个元素，做计算然后再进进栈
        if ( tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
            //弹出两个栈顶元素
            long long num1 = st.top();
            st.pop();
            long long num2 = st.top();
            st.pop();
            //根据不同的符号做运算
            if (tokens[i] == "+") st.push(num1+num2);
            if (tokens[i] == "-") st.push(num2-num1);
            if (tokens[i] == "*") st.push(num1*num2);
            if (tokens[i] == "/") st.push(num2/num1);
        } else {
        //如果遇到了数字，直接进栈就行
            st.push(stoll(tokens[i]));//stoll将传入的字符串转换成long long int
            //stol将传入的参数转换成long int
        }
    }

    int result = st.top();
    st.pop();
    return result;
}

//6.滑动窗口
class MaxDqueue {
public:
//定义特有的队列，用来维护滑动窗口里面的最大值
//怎么维护呢？
//滑动窗口里的值挨个扫描，如果这个值大于back()的值，则pop_back()
//这样，如果当前扫描到的这个值是滑动窗口中最大的，则会一直pop_back()知道队列中没有没有元素
//这个最大的元素就是当前队列最大的元素
    deque<int> que;//用双端对两列deque来实现最大队列
    //pop函数
    //队列不为空，弹出的数值是队列出口数值的时候弹出
    //注意，这个窗口的最左边的值可能不是队列的front
    //比如[1,22,4,5,6] 队列是[22,4]
    //此时pop，我们显然是想让窗口移动，窗口变成[22, 4, 5, 6, 2]
    //这时候，MaxDeque队列还是[22, 4]
    //如果不检测value == que.front直接进行pop，那么这一步，滑动窗口的移动就直接把22移走了，
    //这是错误的。因为下一个滑动窗口的最大值显然还是22，但是22被移动走以后，就成了4了
    void pop(int value) {
        if (!que.empty() && value == que.front()) {
            que.pop_front();
        }
    }
    //push函数
    void push(int value) {
        //循环检测当前队尾元素和待入队元素的大小，我们要找到的是最大的元素
        //如果，待入队元素比队尾的元素大，那就一直弹出队尾元素，知道找到一个比待入队元素大的
        //或者，到对空，如果到对空，那么入队的这个元素就是当前MaxDqueue的max且是front元素
        while (!que.empty() && value > que.back()) {
            que.pop_back();
        }
        que.push_back(value);
    }

    //front返回队头元素，对头元素就是当前滑动数组中的max元素
    int max_front() {
        return que.front();
    }
};

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//描述：
/*
给一个数组nums和一个滑动窗口的大小k,滑动窗口每次往后移动一个单位
问？每次移动窗口后，这个窗口里面的最大值是那个数字，并将每次移动的最大值添加到vector中并返回
*/
    MaxDqueue que;//定义滑动窗口即，最大元素队列
    vector<int> result;//定义vector用来保存每次移动滑动窗口的结果
    //将前面k个元素放入滑动窗口，当然因为我们定义了MaxDqueue，所以放入滑动窗口的都是front是最大元素的
    for (int i = 0; i < k; i++) {
        que.push(nums[i]);
    }
    //获取到第一个滑动窗口的max
    result.push_back(que.max_front());
    //滑动串口移动
    for (int i = k; i < nums.size(); i++) {
        que.pop(nums[i - k]);//删除滑动窗口的最左边的元素，注意，这个元素不一定是队头元素
        que.push(nums[i]);//将当前扫描到的元素加入滑动窗口，同时也加入MaxDeque队列
        result.push_back(que.max_front());//获取每一次的队头元素，即窗口最大元素加入result数组中
    }
    return result;
}

//7.前k个高频元素
class CMP{
//定义比价器对象。因为我们在创建小顶堆的时候，要使用比较。
//我们做比较的对象是map的pair，每个pair都是由键值对构成的
//我们只希望对pair的value进行比较，所有要定义CMP对对小顶堆的比较形式进行说明
public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;//这里定义成了>，表明是小顶堆，如果是<则是大顶堆
    }
};

vector<int> topKFrequent(vector<int>& nums, int k) {
    //要统计元素出现的频率
    unordered_map<int, int> map;//每个pair键用来保存数字，值用来保存这个数字出现的次数
    for (int i = 0; i < nums.size(); i++) {
        map[nums[i]]++;
    }

    // 对频率进行排序
    //定义小顶堆，大小为k，就是要求的前k个高频元素,第三个参数是cmp
    //这个优先队列底层是由vector构成的，vector的每一个元素都是一个pair<int, int>
    //使用自定义的CMP只对pair的值进行排序
    priority_queue<pair<int, int>, vector<pair<int, int>>, CMP> pri_que;

    //定义好小顶堆以后，就要遍历我们刚才计算出来的map
    //用map的迭代器挨个扫描map中的每一个pair,让其进入小顶堆
    //同时保持小顶堆中元素的数量为k个，如果大于k个就要pop堆顶元素
    for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
        pri_que.push(*it);
        if (pri_que.size() > k){
            //如果小顶堆元素大于K了，就要将此事堆中最小的那个元素pop出去，
            //始终保持堆中只有K个元素
            //cout << (*it).first << endl;
            pri_que.pop();
        }
    }


    //此时最终的小顶堆已经构建完成，我们要将小顶堆中的的数据按照从大到小的数据放入vector中
    //注意：小顶堆的top和pop返回的都是堆顶元素，堆顶元素是最小的值
    //所以，要获得从大到小排序的数组，就要把最先出堆的元素放在vector的第k-1个位置
    vector<int> result(k);//定义一个vector，里面的元素个数是k个
    for (int i = k-1; i >= 0; i--) {
        result[i] = pri_que.top().first;//我们此时是要将键放入vector中，
        //键是数字，值是数字出现的数量
        pri_que.pop();//每次获取完堆顶的元素以后，要pop，这样堆顶，也就是最小的元素才会更新
    }

    return result;
}

#endif // STACK_QUEUE_H_INCLUDED
