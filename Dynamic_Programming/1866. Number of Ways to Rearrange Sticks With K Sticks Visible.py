# TC:O(n * k) SC:O(k)可優化到k 程式碼中是n * k
class Solution:
    def rearrangeSticks(self, n: int, k: int) -> int:
        '''
        又是一道讓你排1 ~ n 題目 並且他需要你排出最長遞增子序列為k的排法有多少種
        n = k = 1000
        所以n * k時間複雜度是可以接受的 也就是選到i位置時能夠組成j長度的可見高的棍子有多少種方案?
        '''
        MOD = 10 ** 9 + 7
        f = [[0] * (k + 1) for i in range(n + 1)]
        f[0][0] = 1
        for i in range(n):
            for j in range(k):
                f[i+1][j+1] = (f[i][j] + (i) * f[i][j+1]) % MOD
        return f[-1][-1]

