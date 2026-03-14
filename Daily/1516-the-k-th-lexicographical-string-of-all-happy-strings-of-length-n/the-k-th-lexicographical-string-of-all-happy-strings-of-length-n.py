class Solution:
    def getHappyString(self, n: int, k: int) -> str:
        '''
        最多就是 3 * 2 ^ (n - 1) 
        3 * 2 ^ (n - 1) > (k - 1) -> 第一個字母
        '''
        if k > 3 << (n - 1):
            return ""
        k -= 1
        ans = [ord('a')] * n
        ans[0] += k >> (n - 1) # 直接告訴你在哪個block 概念, 2 ^ (n - 1)為block size
        for i in range(1, n):
            ans[i] += k >> (n - i - 1) & 1
            if ans[i] >= ans[i - 1]:
                ans[i] += 1
        return "".join(map(chr, ans))
