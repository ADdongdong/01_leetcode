#ifndef _DOUBELPOINTERTEST_H_INCLUDED
#define _DOUBELPOINTERTEST_H_INCLUDED
#include "00_DooubeePointer.h"
#include <iostream>
using namespace std;

//1.removeElementTest
void removeElementTest(){
    vector<int> nums = {1,2,3,3,4,5};
    int result = removeElement(nums, 3);
    cout << result << endl;
}


#endif // 01_DOUBELPOINTERTEST_H_INCLUDED
