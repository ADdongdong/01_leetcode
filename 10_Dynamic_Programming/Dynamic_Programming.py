#Definition for a binary tree node.
class TreeNode:
    #python中的__init__函数返回值为None,但是事实上会初始化一个对象，并返回这个对象的引用
    def __init__(self, val = 0, left=None, right=None) -> None:
        self.val = val 
        self.left = left
        self.right = right

    #手动先序生成二叉树
    #这里将buildTree()和函数声明为staticmethod方法
    #因为这个方法和类的实例没有关系，即我们调用这个方法，不用实例一个类对象再通过对象调用也可以
    #这只是一个单独的函数，也就是，写到类外面也是完全可以的，
    #所以声明为staticmethod方法
    @staticmethod
    def bulidTree():
        val = int(input('请输入当前结点的值：'))
        if val == -1:
            return None
        
        node = TreeNode(val)
        node.left = TreeNode.bulidTree()
        node.right = TreeNode.bulidTree()

        return node
        
        


class Solution:
    def workBreak(self, s: str, wordDict: list[str]) -> bool:
        #排列
        dp = [False]*(len(s) + 1)
        dp[0] = True
        #遍历背包
        for j in range(1, len(s) + 1):
            # 遍历单词
            for word in wordDict:
                if j >= len(word):
                    #python中字符串切片用s[开始下标，终止下标]
                    dp[j] = dp[j] or (dp[j - len(word)] and word == s[j - len(word):j])
            print(dp)
        return dp[len(s)]
    
    #打家劫舍遍历逻辑
    def robRange(self, nums: list):
        l = len(nums)
        dp = [0]*l
        dp[0] = nums[0]
        for i in range(1, l):
            if i == 1:
                dp[i] = max(dp[i-1], nums[i])
            else:
                dp[i] = max(dp[i-1], dp[i-2] + nums[i])
            print(dp)
        #返回dp数组的最后一个元素
        return dp[-1]



    #打家劫舍
    def rob(self, List: list):
        result = self.robRange(List)
        return result
        '''
        if len(List) == 0: 
            return 0
        if len(List) == 1:
            return max(List[0], List[1])
        #初始化dp数组
        dp = [0]*len(List)
        dp[0] = List[0]
        dp[1] = max(dp[0], List[1])
        #进入for循环
        for i in range(2, len(List)):
            dp[i] = max(dp[i-1], dp[i-2] + List[i])
            print(dp) 

        return dp[len(List) - 1]

        '''

    #打家劫舍2
    def rob_2(slef, nums: list):
        if len(nums) == 0:
            return 0
        if len(nums) == 1:
            return nums[0]
        #情况1 从第1个元素到最后一个元素
        #python的数组切片是左闭右开的
        result1 = slef.robRange(nums[1:])
        #情况2 从第0元素到倒数第二个元素
        result2 = slef.robRange(nums[:-1])
        return max(result1, result2)
        

    #打家劫舍3
    def robTree(self, node : TreeNode) -> tuple:
        #递归终止的条件
        if node == None:
            return (0,0)
        #递归遍历左右子树
        left = self.robTree(node.left)
        right = self.robTree(node.right)

        #如果不偷当前结点 dp[0]
        val0 = max(left[0], left[1]) + max(right[0], right[1])
        #如果偷当前结点 dp[1]
        val1 = node.val + left[0] + right[0]
        return (val0, val1)
        
    def rob3(self, root: TreeNode) -> tuple:
        dp = self.robTree(root)
        return max(dp[0], dp[1])

    


        