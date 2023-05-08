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
                    dp[j] = dp[j] or (dp[j - len(word)] and word == s[j - len(word):j])
            print(dp)
        return dp[len(s)]

#定义测试函数
def test():
    slu = Solution()
    wordList = ["leet","code"]
    s = "leetcode"
    result = slu.workBreak(s, wordList)
    print(result)


test()
