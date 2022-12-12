#ifndef _HASHTABLE_H_INCLUDED
#define _HASHTABLE_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//定义打印vector的函数模板
template<class T>
void PrintVector(vector<T> v){
    //gcc编译器无法识别vector<T>::iterator是一个类型
    //所以，前面要加上typename/class来说明这是一个类型
    typedef class/*class*/ vector<T>::iterator IT;
    for(IT it = v.begin(); it != v.end(); it++){
            cout << *it << ' ';
    }
    cout << endl;
}

//定义打印二维vector的函数
void PrintDim2Vector(vector<vector<int>> v){
    for (auto& row : v){
        cout << "[";
        for (auto& ele : row){
            cout << ele <<"," ;
        }
        cout <<"]" <<endl;
    }
}

//1.有效的字母异位词
bool isAnagram(string s, string t){
//思路
//单词都是由26个字母组成的，所以，先把s这个单词映射在一个有26个元素的数组record上
//0->a ,15->z,
//step1：将字符串s映射到record上，s中的一个字母出现一次，将record中对应位置下+1
//step2：检查遍历字符串t，t中哪个字母出现一次，在record对应字母下-1
//step3：检查record，如果record数组都是0，则说明s和t构成字母异位的单词
    int record[26] = {0};
    for(int i = 0; i < s.size(); i++){
        record[s[i] - 'a']++;//该字母在record下对应的数字+1
    }
    for(int i = 0; i < t.size(); i++){
        record[t[i]-'a']--;//该字母在recored下对应的数字-1
    }
    //检查record数组
    for(int i = 0; i < 26; i++){
        if(record[i] != 0){
            return false;
        }
    }
    return true;
}

//2.两个数组的交集
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> result_set;//这个set来保存结果
    //所有向量和向量衍生容器都有迭代器，begin()函数会返回开始迭代器，
    //这个迭代器默认指向容器的首个元素
    unordered_set<int> nums_set(nums1.begin(), nums1.end());//用向量nums1生成一个set
    //其实可以理解为，多nums1中的元素去重，然后保存到nums_set中
    for (int num : nums2){//遍历nums2中的元素
        if(nums_set.find(num) != nums_set.end()) {
        //注意，这里nums_set.end()其实就可以理解为空NULL
        //也就是说，在nums_set中寻找nums2中的每一个元素
        //如果寻找的结果不是空。这就是if判断里面的意思。

        //如果，如果在nums1映射的集合nums_set中找到了
        //就把这个元素添加到result_set中。也就是求交集了。
            result_set.insert(num);
        }
    }
    return vector<int>(result_set.begin(), result_set.end());
}

//3.快乐数
int getSum(int n){
//这个函数用来计算十位上数字平方与个位上数字平法的和
    int sum = 0;
    //输入一个二位数，while会循环两次
    //第一次计算十位平方
    //第二次计算个位的平方
    //此时，n /= 10 的结果就是0了，while循环结束
    while(n){
        sum += (n%10)*(n%10);
        n /= 10;//34->3->0
    }
    return sum;
}

bool isHappy(int n){
//这个函数用来判断是不是happy number
//关键点：
//对于一个二位数来说，只有两种情况，要么是快乐数，要么不是快乐数
//是快乐数：不断计算，最后结果是1
//不是快乐数：不断计算，最后结果不是1,
//那什么情况下最后的结果不是1呢？
//那就是，计算可能陷入了死循环sum出现多次，当然，能出现2次，则必然会出现无数次
//如何判断一个数字是否重复出现呢？使用unordered_set
    unordered_set<int> set_record;//这个用来记录计算过程中sum出现过的数字
    while(1){
        int sum = getSum(n);
        if(sum == 1){
            return true;
        }
        if(set_record.find(sum) != set_record.end()){
        //如果此时计算出来的sum在set_record出现过，说明已经陷入循环了
            return false;
        }else{
        //如果此时的sum没有在set_record中出现过，则加入set_record，等待后面的检测
            set_record.insert(sum);
        }
        n = sum;//每次刷新n的值，不然永远都是false,哈哈
    }
}

//4.两数之和
vector<int> twoSum(vector<int>& nums, int target){
//题目描述：
/*给定一个整数数组nums和一个目标值target
 *请你在数组中找出和为目标值的那两个整数，
 *并返回他们的数组下标。（返回的值保存在一个数组中）
 *假设每种输入只会对应一个答案。
 *但是，数组中同一个元素在答案里不能重复出现
 */

//关键点：
//每种输入会对应一个答案，数组中同一个元素在答案中不能重复出现
//思路：
//遍历一个元素，将一个元素和其下标打包放在map中，元素值作为key,下标作为value
//这样可以保证，是正在遍历的元素和已经遍历过的元素做组合，保证了数组元素不重复出现
//而且，map中的元素值和下标值都保存成了pair所以，也方便获取下标
    unordered_map<int, int> _map;//建立一个空map,用来保存已经访问过的元素
    for (int i = 0;  i < nums.size(); i++){
        typedef typename unordered_map<int ,int>::iterator IT;//重命名map的迭代器
        //遍历当前元素，并在map中寻找是否有匹配的key
        IT iter = _map.find(target - nums[i]);//在map中找有没有能匹配上的元素
        if (iter != _map.end()){
            //如果匹配值能在map中找到，则返回这两个数的下标
            return {iter->second, i};//iter->second是map元素对应的value
            //i是当前遍历数组的下标
        }
        //如果没有找到匹配对，就把访问过的元素和下标加入到map中
        _map.insert(pair<int, int>(nums[i]/*key*/, i/*value*/));
    }
    return {};
}

//5.四个数字相加
int fourSumCount(vector<int> A, vector<int> B, vector<int> C, vector<int> D){
//描述:
/*A,B,C,D四个数组，计算有多少个(i,j,k,l)是的A[i] + B[i] + C[i] + D[i] = 0
 *所以这个题的返回值是int
 */
//思路:
/*这个题和上个题有相同的地方，先用map记录A,B数组中所有两数之和，和每种情况出现的次数
 *再遍历C,D数组，边遍历边在map中寻找0-(c+d)。
 *因为这个数字肯定已作为pair记录在map中了
 *每找到一组，就给count加上一个pair对应的value
 */

    unordered_map<int, int> umap;//创建一个map，来记录A和B所有元素之和可能出现的情况和出现的次数
    //遍历A,B两个数组，并统计所有元素之和和出现的次数
    for (int a : A){
        for (int b: B){
            umap[a + b]++;//这种添加map中键值对的方式和python字典是一样的
            /*
             *umap.insert(pair<int, int>(a+b, ??)
             *使用insert函数的话，value部分不好写实时更新
             *所以，用mapName[key]++这种方式来迭代key所对应value的值
             */
        }
    }
    //统计a+b+c+d = 0 出现的次数
    int _count = 0;
    // 再遍历C和D数组，如果找到 0-(c+d) 在map中出现过的话，
    // 就把map中key对应的value加到_count中
    for (int c : C){
        for (int d : D){
            if (umap.find(0 - (c+d)) != umap.end()) {
                _count += umap[0 - (c + d)];
                cout << "更新_count:" << _count << endl;
            }
        }
    }
    return _count;
}

//6.赎金信
bool canConstruct(string ransomNote, string magazine){
//描述：
//判断ransomNote这个字符串是否可以由magazine这个字符串表示出来
//注意，magazine中的字符不能重复使用，每个字符只能使用一次
//思路：
//把magazine中的出现了那些字符，每个字符出现了多少次用一个数组记录下来
//遍历ransomNote字符串，每遍历到一个字符，去数组对应的位置下-1
//最后，检查这个数组，是否出现了<0，如果出现了<0的情况
//说民，magazine中的字符不够表示ransomNote
    vector<int> recode(26, 0);//定义一个全为0的数组
    PrintVector(recode);//打印这个空数组
    //遍历magazine字符串
    for(int i = 0; i < magazine.size(); i++){
        recode[magazine[i] - 'a']++;//对应的字符出现的次数++
    }
    PrintVector(recode);//打印记录后的数组
    //遍历ransomNote字符串
    for(int i = 0; i < ransomNote.size(); i++){
        recode[ransomNote[i] - 'a']--;//对应位置出现字符--
    }
    PrintVector(recode);
    //检查recorde数组
    for (int i:recode){
        if(i < 0){
            return false;//如果有一个字符不够，都返回false
        }
    }
    return true;
}

//7.3数字之和
vector<vector<int>> threeSum(vector<int>& nums){
//描述：
/*给一个包含n个整数的数组nums，判断nums中是否存在三个元素a,b,c
 *使得a + b + c = 0
 *找出所有满足条件且不重复的三元组
 *注意，答案中不可以包含重复的三元组
 */
//思路：
/*双指针法plus三指针法
 *1.先将这个无序的vector排序从小到大
 *2.如果第一个元素即最小的元素就是大于0的，那不可能有三个加起来还等于0
 *3.i指向[0],left指向i+1,right指向最后一个元素即nums.size()-1
 *4.i和left一直往后走，right往前走，那什么时候走呢
 *5.计算sum = nums[i]+nums[left]+nums[right]的值，如果等于0则保存着三个数的值
 *6.如果sum<0,那说明,left的值小了，要left大一些才行，left++
 *7.如果sum>0,那说明,right的值大了，要right小一些才行，right--
 *8.对于每一个i,当left和right指向同一个元素的时候，就结束，i++
 *9.如何去重？
 *10.如果nums[i]==nums[i-1]那说明，此时如果有left，那么left初试是和i相等的，所以i++
 *这样，可以保证尽可能省时间，而且，能做到去重，思路也比价清晰
 */
    //开始写代码
    //先创建一个二维数组，用来保存最后的结果
    vector<vector<int>> result;
    //将给定的数组排序
    sort(nums.begin(), nums.end());
    //只要排序后第一个元素的值大于0，那就不可能有三数值和为0的情况
    if (nums[0] > 0){
        return result;//直接返回空列表，程序结束
    }
    //开始遍历nums，对于每一个i,都都要找一轮left和right,同时要去重
    for (int i = 0; i < nums.size(); i++){
        //先进行去重，看看相邻两个元素是否相同
        // 错误去重a方法，将会漏掉-1,-1,2 这种情况why
        /*
        if (nums[i] == nums[i + 1]) {
            continue;
        }
        */
        if ( i > 0 && nums[i] == nums[i-1]){
            continue;
        }
        //定义left和right
        int left = i + 1;
        int right = nums.size() - 1;
        while (left < right){
        //当left==right的时候，本轮循环结束
            //当三数字之和大于0时，减小right
            if(nums[i] + nums[left] + nums[right] > 0) right--;
            //当三数字之和小于0时，增加left
            else if(nums[i] + nums[left] + nums[right] < 0) left++;
            //剩下的情况就是三数字之和等于0了，加入到reslut
            else{
                 result.push_back({nums[i], nums[left], nums[right]});
                 //同样，对left和right进行去重
                 while (right > left && nums[right] == nums[right-1]) right--;
                 while (right > left && nums[left] == nums[left+1]) left++;

                 //此时，找到了一个答案，而且也进行了去重更新left和right
                 left++;
                 right--;
            }
        }
    }
    return result;//返回最终结果
}

#endif // 00_HASHTABLE_H_INCLUDED
