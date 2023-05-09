from Dynamic_Programming import Solution

class Test():
    def __init__(self) -> None:
        self.slu = Solution()
        self.nums1 = [1,2,3,1]
        self.nums2 = [1,2,3]
    
    #定义测试函数
    def wordBreaktest(self):
        slu = Solution()
        wordList = ["leet","code"]
        s = "leetcode"
        result = slu.workBreak(s, wordList)
        print(result)

    #测试打家劫舍
    def robTest(self):
        result = self.slu.rob(self.nums1)
        print(result)

    def rob2Test(self):
        #nums2 :1,2,3
        result = self.slu.rob_2(self.nums2)
        print(result)

    def main(self, test: callable):
        test()
        

if __name__ == "__main__":
    test = Test()
    test.main(test.rob2Test)