#ifndef DYNAMIC_PROGRAMMING_TEST_H_INCLUDED
#define DYNAMIC_PROGRAMMING_TEST_H_INCLUDED
#include <iostream>
#include <vector>
#include "Dynamic_Programming.h"

using namespace std;

//1 斐波那契树
void fibTest() {
    int n = 10;
    int result = fib(n);
    cout << result << endl;
}
#endif // DYNAMIC_PROGRAMMING_TEST_H_INCLUDED
