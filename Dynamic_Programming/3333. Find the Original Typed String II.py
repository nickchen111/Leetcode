# TC:O(n + k^2) SC:O(k^2)
class Solution:
    def possibleStringCount(self, word: str, k: int) -> int:
        '''
        字串至少要有k長度 問說他可以犯錯0 ~ 很多次 能有幾種可能
        n = 1e5
        k = 2000
        正難則反
        1. n < k 沒方案
        '''
        MOD = 10 ** 9 + 7
        n = len(word)
        if n < k:
            return 0
        cnts = []
        cnt = 0
        ans = 1
        for i in range(n):
            cnt += 1
            if i == n - 1 or word[i] != word[i + 1]:
                if cnt > 1:
                    if k > 0:
                        cnts.append(cnt - 1) # 每個物品都選了一個的狀況下 還可以選多少個
                    ans = ans * cnt % MOD
                k -= 1
                cnt = 0
        if k <= 0:
            return ans # 隨便選都合法
        dp = [[0] * k for _ in range(len(cnts) + 1)]
        dp[0] = [1] * k # 都不選也是一種方案
        for i, c in enumerate(cnts):
            s = list(accumulate(dp[i], initial = 0))
            for j in range(k):
                dp[i + 1][j] = (dp[i + 1][j] + s[j + 1] - s[max(0, j - c)]) % MOD
        return (ans - dp[-1][-1]) % MOD
                
