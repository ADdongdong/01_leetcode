#ifndef GREEDY_ALGORITHM_H_INCLUDED
#define GREEDY_ALGORITHM_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*1 分发饼干
 *假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
 *对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；
 *并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，
 *个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

 *示例 1:
 *输入: g = [1,2,3], s = [1,1]
 *输出: 1 解释:你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
 *             虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
 *             所以你应该输出1。
 *示例 2:
 *输入: g = [1,2], s = [1,2,3]
 *输出: 2
 *解释:你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
 *你拥有的饼干数量和尺寸都足以让所有孩子满足。所以你应该输出2.
 *
 *思路：
 *大饼干可以满足大胃口的孩子和小胃口的孩子，
 *小饼干只能满足小胃口的孩子。
 *所以，为了能让更多的小朋友被满足，所以，要让最大的饼干去满足胃口最大的孩子。
 *如果满足不了，就满足胃口次之的孩子，然后，依次类推。
 */
int findContentChildren(vector<int>& g, vector<int>& s) {
    //对孩子列表和饼干列表进行排序
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int num = 0;//定义num就是最大可以满足的孩子的数量
    //然后遍历饼干列表，如果s[i] > g[j] 那么就num+1，i++,j++，不然就j++
    int i = g.size()-1;
    int j = s.size()-1;
    while (i >= 0 && j >= 0){
        if (s[j] >= g[i]){
            //如果当前饼干能满足当前孩子的胃口，那么就继续检查下一个饼干和下一个孩子
            num++;
            i--;
            j--;
        }else {
            //如果当前饼干不能满足当前孩子，说明当前孩子胃口太大，只能检查下一个孩子
            i--;
        }
    }
    /*
    int index = s.size() -1;
    int result = 0;
    for (int i = g.size() - 1; i >= 0; i++) {
        if (index >=0 && s[index] >= g[i]) {
            result++;
            index--;
        }
    }*/
    return num;

}

#endif // GREEDY_ALGORITHM_H_INCLUDED
