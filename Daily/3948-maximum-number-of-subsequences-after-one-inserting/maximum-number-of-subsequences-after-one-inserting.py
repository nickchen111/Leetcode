class Solution:
    def numDistinct(self, s:str, t:str) -> int:
        n, m = len(s), len(t)
        if n < m:
            return 0
        dp = [1] + [0] * m
        for i, x in enumerate(s):
            prev = dp[0]
            for j, y in enumerate(t):
                tmp = dp[j+1]
                dp[j+1] = prev + dp[j+1] if x == y else dp[j+1]
                prev = tmp
        return dp[m]
        # dp = [[0] * (m + 1) for _ in range(n + 1)]
        # dp[0][0] = 1
        # for i, x in enumerate(s):
        #     dp[i + 1][0] = 1
        #     for j, y in enumerate(t):
        #         dp[i + 1][j + 1] = dp[i][j] + dp[i][j + 1] if x == y else dp[i][j + 1]
        # return dp[-1][-1]
    def calcInsertC(self, s:str) -> int:
        t = s.count('T')
        l = ans = 0
        for ch in s:
            if ch == 'L':
                l += 1
            elif ch == 'T':
                t -= 1
            ans = max(ans, l * t)
        return ans
    def numOfSubsequences(self, s: str) -> int:
        extra = max(self.numDistinct(s, "CT"), self.numDistinct(s, "LC"), self.calcInsertC(s))
        return self.numDistinct(s, "LCT") + extra