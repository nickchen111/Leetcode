# 前後綴分解 TC:O(n) SC:O(n) -> O(1)
class Solution:
    def numOfSubsequences(self, s: str) -> int:
        n = len(s)
        t = s.count('T')
        l = lc = ct = c = lt = lct = 0
        ans = 0
        for ch in s:
            if ch == 'L':
                l += 1
            elif ch == 'C':
                lc += l
                c += 1
            elif ch == 'T':
                lct += lc
                ct += c
                t -= 1
            lt = max(lt, l * t)
        return lct + max(lt, ct, lc)

        '''
        SC:O(n)做法
        preL = [0] * (n + 1)
        preLC = [0] * (n + 1)
        totalL = totalLC = 0
        total = 0

        for i in range(n):
            if s[i] == 'L':
                totalL += 1
            elif s[i] == 'C':
                totalLC += totalL
            elif s[i] == 'T':
                total += totalLC
            preL[i + 1] = totalL
            preLC[i + 1] = totalLC

        sufT = [0] * (n + 1)
        sufCT = [0] * (n + 1)
        totalT = totalCT = 0
        for i in reversed(range(n)):
            if s[i] == 'T':
                totalT += 1
            elif s[i] == 'C':
                totalCT += totalT
            sufT[i] = totalT
            sufCT[i] = totalCT

        max_add = 0
        for i in range(n + 1):
            max_add = max(max_add, sufCT[i])
            max_add = max(max_add, preL[i] * sufT[i])
            max_add = max(max_add, preLC[i])

        return total + max_add
        '''
# LCS 雙序列DP + 前後綴分解 
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

