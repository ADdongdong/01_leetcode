from Dynamic_Programming import Solution

class Test():
    #定义测试函数
    def wordBreaktest(self):
        slu = Solution()
        wordList = ["leet","code"]
        s = "leetcode"
        result = slu.workBreak(s, wordList)
        print(result)

    def robTest(self):
        slu = Solution()
        List = [1,2,3,1]
        result = slu.rob(List)
        print(result)

    def main(self, test):
        test()
        

if __name__ == "__main__":
    test = Test()
    test.main(test.robTest)