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
        
    


        