# LC. 516
class Solution:
    def countArrangement(self, n: int) -> int:
        u = (1 << n) - 1
        @cache  # 缓存装饰器，避免重复计算 dfs 的结果（记忆化）
        def dfs(s: int) -> int:
            if s == u:
                return 1
            res = 0
            i = s.bit_count() + 1 # 1 - index
            for j in range(1, n + 1):
                if s >> (j - 1) & 1 == 0 and (i % j == 0 or j % i == 0):
                    res += dfs(s | (1 << (j - 1)))
            return res
        return dfs(0)

class Solution:
    def countArrangement(self, n: int) -> int:
        f = [0] * (1 << n)
        f[0] = 1
        for s in range(1, 1 << n):
            i = s.bit_count()
            for j in range(1, n + 1):
                if s >> (j - 1) & 1 and (i % j == 0 or j % i == 0):
                    f[s] += f[s ^ (1 << (j - 1))]
        return f[-1]
