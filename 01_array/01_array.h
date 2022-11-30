#ifndef _ARRAY_H_INCLUDED
#define _ARRAY_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>>::iterator IT_matrix;//二维数组迭代器重命名
typedef vector<int>::iterator IT;

void Print(vector<int>);

class Solution{
public:
    //1.二分查找
    int Search(vector<int>&, int);

    //2.用快慢指针，移除数组中指定元素
    int Remove(vector<int>&, int);

    //3.对数组平方后再排序
    vector<int> sortedSquares(vector<int>&);

    //4.长度最小的子数组(用滑动窗口求解,双指针法)
    int minSubArrayLen(int, vector<int>&);

    //5.螺旋矩阵
    vector<vector<int>> generateMatrix(int);

};

//1.二分查找
int Solution::Search(vector<int>& nums, int target){
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right){
        //计算middle位置
        int middle = left + ((right - left)/2);
        if(nums[middle] > target){
            //若middle值大于了target,说明目标值在列表的左半部分，且middle值不是target
            right = middle - 1;
        }else if(nums[middle] < target){
            //若middle值小于target，说明目标值在列表的右半部分，且middle值不是target
            left = middle + 1;
        }else{
            //若middle值等于target,那就说明，此时这个middle值就是我们要求的target
            return middle;
        }
    }
    //如果到最后都没找到，返回-1，表示查找失败
    return -1;
}

//2.用快慢指针，移除数组中指定元素
int Solution::Remove(vector<int>& nums, int target){
    int slowIndex = 0;
    for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++){
        if(target != nums[fastIndex]){
        //如果快指针指向的不是target
        //那就让快指针指向的元素往前移动一个单位
            nums[slowIndex++] = nums[fastIndex];
        //比如：1,2,4,5,6 删除2
        //1不是target，num[0]=nums[0]，其实是同一个位置自赋值，不改变值大小
        //2是target, slowIndex不动，fastIndex++
        //4,5,6都不是target,那整体往前移动
        }
    }
    return slowIndex;
}

//3.对数组平方后再排序
vector<int> sortedSquares(vector<int>& nums){
    int k = nums.size() - 1;//初始化result数组指针
    vector<int> result(nums.size(), 0);//初始化resulut数组，所有元素初始化为0
    for(int i = 0, j = (nums.size() - 1); i <= j;){//这里要有=，不然奇数个的数组会少一个元素
        //平方最大的值只可能出现在两头-4,-3,-2,-1,1,2,3,4
        //所以,i指向数组头元素，j指向数组尾元素
        //平方后做比较，谁大，把谁放到resulut的靠后位置
        if(nums[i] * nums[i] < nums[j]*nums[j]){
            //如果头元素平方小于尾元素平方
            result[k--] = nums[j]*nums[j];
            j--;//尾元素指针往前走,做--
        }else{
            result[k--] = nums[i] * nums[i];
            i++;//头元素指针往后走,做++
        }
    }
    return result;
}

//4.长度最小的子数组(用滑动窗口求解,双指针法)//注意target>0
int minSubArrayLen(int target, vector<int>& nums){
    int result = INT_MAX;//result表示最后输出的结果
    int sum = 0;
    int j = 0;//慢指针，注意，慢指针也是全局变量
    int subLength = 0;//当前最小自组的长度
    for (int i=0; i < nums.size(); i++){
        sum += nums[i];
        //cout << sum << endl;
        while(sum >= target){
        //当sum的值大于target,说明这个子组有缩小的可能，
        //怎么缩小呢？j++,让慢指针往前走一步
        //如果往前走一步仍然符合target < sum，那就更新result的值
        subLength = i - j + 1;//当前自组的长度
        sum -= nums[j++];//j往前走，说明自组少了一个元素
        result = result < subLength ? result:subLength;//更新最小子组
        }
    }
    return result == INT_MAX ? 0 : result;
    //如果找到了，那么result的初始值必然会被改变，若没改变，说明没有最小自组
}

//5.螺旋矩阵
vector<vector<int>> generateMatrix(int n){
    vector<vector<int>> res(n, vector<int>(n, 0));
    //定义一个二维数组，shape为n*n
    int startx = 0, starty = 0;//每一圈循环的起始位置
    int loop = n/2;//要循环多少圈，3*3的矩阵，循环1圈，画图就理解了
    int mid = n/2;//矩阵的中间位置
    int cou = 1;//赋值变量，没给一个位置赋值，cou++
    int offset = 1;//控制每一条边遍历的长度，每循环一圈，offset++
    int i, j;
    while (loop--){
        //第一圈从(0,0)元素开始
        i = startx;
        j = starty;

        //模拟一圈循环，一圈大循环分为4个小循环
        //最上一行，从左到右(左闭右开，就是不算最上一行的最后一个元素)
        for(j = starty; j < n - offset; j++){
            res[startx][j] = cou++;//最上面一行，行x不变，列y++
        }

        //最右边一列，从上到下(上闭下开，就是不算最右边的最底下一个元素)
        for(i = startx; i < n - offset; i++){
            res[i][j] = cou++;//最右边一行，列y不变，行x++
        }

        //最下边一行，从右到左(右闭左开，就是不算最下一行的最左边一个元素)
        for(; j > starty; j--){
            res[i][j] = cou++;//最下一行，行x不变，列y--
        }

        //最左边一列，从下到上(下闭上开)
        for(; i > startx; i--){
            res[i][j] = cou++;
        }

        //第二圈开始的时候，起始坐标位置丛(0,0)->(1,1),后面以此类推
        startx++;
        starty++;

        //用offset控制每一条边的长度
        offset++;
    }
    //如果n为奇数，需要单独给矩阵最中间的位置赋值
    if(n%2){
        res[mid][mid] = cou;
    }
    return res;
}

//一维数组打印
void Print(vector<int> v){
    for(IT it = v.begin(); it!= v.end(); ++it){
        cout << *it << ' ';
    }
    cout << endl;
}

//二维数组打印
void Print_matrix(vector<vector<int>> v){
    for(IT_matrix it = v.begin(); it!= v.end(); it++){
             Print(*it);
        }
}
#endif // 01_ARRAY_H_INCLUDED
