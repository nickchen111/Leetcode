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
        f = [[0] * 3 for _ in range(n+1)]
        for i in range(n):
            f[i+1][0] = f[i][0]
            f[i+1][1] = f[i][1]
            f[i+1][2] = f[i][2]
            if nums[i] == 0:
                f[i+1][0] = (f[i+1][0] * 2 + 1) % MOD
            elif nums[i] == 1:
                f[i+1][1] = (f[i+1][1] * 2 + f[i][0]) % MOD
            else: 
                f[i+1][2] = (f[i+1][2] * 2 + f[i][1]) % MOD
            
        return f[n][2] % MOD
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
