# TC:O((n * n * k) * 2 / 27) SC:O(n * k)
min = lambda a, b: b if b < a else a
max = lambda a, b: b if b > a else a
class Solution:
    def minXor(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [[inf] * (n + 1) for _ in range(k + 1)]
        dp[0][0] = 0
        for i in range(1, k + 1): # 要分幾組
            xor_val = 0
            for j in range(i, n - (k - i) + 1): # 前面至少幾組 後面至多可以放幾組 n - (k - i) 
                xor_val = 0
                for t in range(j - 1, i - 2, -1):
                    xor_val ^= nums[t]
                    dp[i][j] = min(dp[i][j], max(xor_val, dp[i-1][t]))
        return dp[k][n]

        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int:
            if i == 0:
                return 0 if j < 0 else inf
            xor_val = 0
            ans = inf
            for t in range(j, i - 2, -1): # 剩下 i組 已經分了 k - i 組 -> t >= i - 1
                xor_val ^= nums[t]
                ans = min(ans, max(xor_val, dfs(i - 1, t - 1)))
            return ans
        return dfs(k, n - 1)
        '''
