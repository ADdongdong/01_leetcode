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
    
    #打家劫舍
    def rob(self, List: list):
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
