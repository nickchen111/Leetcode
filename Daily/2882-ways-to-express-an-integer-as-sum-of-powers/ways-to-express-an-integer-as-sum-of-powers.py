class Solution:
    def numberOfWays(self, n: int, x: int) -> int:
        MOD = 10 ** 9 + 7
        high = ceil(n ** (1 / x))
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
