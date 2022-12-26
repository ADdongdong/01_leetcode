#ifndef STACK_QUEUE_TEST_H_INCLUDED
#define STACK_QUEUE_TEST_H_INCLUDED
#include "stack_queue.h"
#include <iostream>

using namespace std;

//1.用栈模拟队列测试
void MyQueueTest() {
    //定义自己的队列
    MyQueue _queue;
    _queue.push(0);
    _queue.push(1);
    _queue.push(2);
    _queue.push(3);
    int result = _queue.peek();
    cout << result << endl;
    _queue.pop();
    result = _queue.peek();
    cout << result << endl;
    _queue.pop();
}

//2.用队列模拟栈测试
void MyStackTest() {
    MyStack st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
}

//3.括号匹配检测
void isValidTest() {
    string s = "{{}}{}(]";
    string s2 = "{{}}(())[]";
    cout << isValid(s) << endl;
    cout << isValid(s2) << endl;
}

#endif // STACK_QUEUE_TEST_H_INCLUDED
