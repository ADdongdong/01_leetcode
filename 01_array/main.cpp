#include <iostream>
#include "01_array.h"
using namespace std;

int main()
{

    Solution s1;
    //vector<int> v1 = {2,3,5,6,7};
    //int target = 2;
    //int result = s1.Search(v1, target);
    //cout << result << endl;
    //int result2 = s1.Remove(v1, target);
    //cout << result2 << endl;
    //Print(v1);

    //2.平方重排序测试
    //vector<int> v2 = {-2,-1,2,3,4};
    //Print(v2);
    //Print(sortedSquares(v2));

    //3.最小自组长度测试
    //cout << minSubArrayLen(0, v1) << endl;

    //4.螺旋矩阵测试
    vector<vector<int>> v2 = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> v = generateMatrix(5);
    Print_matrix(v);

    return 0;
}

