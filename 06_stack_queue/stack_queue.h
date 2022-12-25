#ifndef STACK_QUEUE_H_INCLUDED
#define STACK_QUEUE_H_INCLUDED
#include <iostream>
#include <stack>
#include <vector>
#include <deque>

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



#endif // STACK_QUEUE_H_INCLUDED
