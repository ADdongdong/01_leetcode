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



#endif // STACK_QUEUE_TEST_H_INCLUDED
