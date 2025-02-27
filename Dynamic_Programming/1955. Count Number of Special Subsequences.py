# TC:O(n) SC:O(1)
class Solution:
    def countSpecialSubsequences(self, nums: List[int]) -> int:
        '''
        一定要有0 1 2 
        '''
        MOD = 10 ** 9 + 7
        n = len(nums)
        f = [0, 0, 0]
        for v in nums:
            if v == 0:
                f[0] = (f[0] * 2 + 1) % MOD
            elif v == 1:
                f[1] = (f[1] * 2 + f[0]) % MOD
            else:  # v == 2
                f[2] = (f[2] * 2 + f[1]) % MOD
        return f[2]
        '''
        遞推
        domain = 4
        dp = [[0] * domain for _ in range(n+1)]
        dp[0][0] = 1
        for i in range(n):
            for j in range(domain):
                dp[i+1][j] = dp[i][j]
                if j == nums[i] or j == nums[i] + 1:
                    dp[i+1][j] += dp[i][nums[i]]
           
        return dp[n][3] % MOD
        '''
        '''
        遞歸 MLE
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0:
                return 1 if j == 0 else 0
            # 選
            ans = dfs(i-1, j)
            ans += dfs(i-1, nums[i]) if nums[i] + 1 == j or nums[i] == j else 0
            return ans
        return dfs(n-1, 3) % MOD
        '''
