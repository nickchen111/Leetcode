# TC:O(n * min(arrLen, n)) SC:O(min(arrLen - 1, steps))
class Solution:
    def numWays(self, steps: int, arrLen: int) -> int:
        '''
        當前pos = 0, 每次可以停留 or 走左右 問說走了steps次以後可以停留在0的方式有多少種
        代表每個位置他的可能性來自於左+右+當前位置
        '''
        MOD = 10 ** 9 + 7
        mn = min(arrLen - 1, steps)
        f = [0] * (mn + 1)
        f[0] = 1
        for k in range(steps):
            prev, nxt = 0, 0
            farDist = mn if mn < k + 1 else k + 1
            for i in range(0, farDist + 1):
                nxt = f[i+1] if i + 1 <= mn else 0
                prev, f[i] = f[i], (f[i] + prev + nxt) % MOD
        return f[0]
        '''
        遞歸
        @cache
        def dfs(pos:int, k:int) -> int:
            if k == steps:
                return 1 if pos == 0 else 0
            if pos - (steps - k) > 0:
                return 0
            ans1 = dfs(pos + 1, k + 1) if pos + 1 < arrLen else 0
            ans2 = dfs(pos, k + 1)
            ans3 = dfs(pos - 1, k + 1) if pos - 1 >= 0 else 0
            return (ans1 + ans2 + ans3) % MOD
        return dfs(0, 0) % MOD
        '''
