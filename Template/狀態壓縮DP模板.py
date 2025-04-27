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

# 枚舉子集的子集 LC. 3444
class Solution:
    def minimumIncrements(self, nums: List[int], target: List[int]) -> int:
        # 预处理 target 的所有子集的 LCM
        m = len(target)
        lcms = [1] * (1 << m)
        for i, t in enumerate(target):
            bit = 1 << i
            for mask in range(bit):
                lcms[bit | mask] = lcm(t, lcms[mask])

        @cache
        def dfs(i: int, j: int) -> int:
            if j == 0:
                return 0
            if i < 0: 
                return inf
            # 不修改 nums[i]
            res = dfs(i - 1, j)
            # 枚举 j 的所有非空子集 sub，把 nums[i] 改成 lcms[sub] 的倍数
            sub = j
            while sub:
                l = lcms[sub]
                res = min(res, dfs(i - 1, j ^ sub) + (l - nums[i] % l) % l)
                sub = (sub - 1) & j
            return res
        return dfs(len(nums) - 1, (1 << m) - 1)
