class Solution:
    def numberOfWays(self, n: int, x: int) -> int:
        MOD = 10 ** 9 + 7
        high = ceil(n ** (1 / x))
        # 遞推
        f = [0] * (n + 1)
        f[0] = 1
        for num in range(1, high + 1):
            power = num ** x
            for cap in range(n, power - 1, -1):
                f[cap] = (f[cap] + f[cap - power]) % MOD
        return f[n]
        '''
        @cache
        def dfs(left, num) -> int:
            if left == 0:
                return 1
            if left < 0 or num < 1:
                return 0
            return (dfs(left - num ** x, num - 1) + dfs(left, num - 1)) % MOD

        ans = dfs(n, high)
        dfs.cache_clear()
        return ans
        '''
