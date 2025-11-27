# TC:O(n + UlogU) SC:O(U)
MOD = 1_000_000_007
MAX_N = 100_001

# 预处理 2 的幂
pow2 = [1] * MAX_N
for i in range(1, MAX_N):
    pow2[i] = (pow2[i - 1] * 2) % MOD

class Solution:
    def countEffective(self, nums: List[int]) -> int:
        if all(x == nums[0] for x in nums):
            return 1

        or_all = reduce(or_, nums)
        w = or_all.bit_length()
        u = 1 << w

        f = [0] * u
        for x in nums:
            f[x] += 1
        for i in range(w):
            bit = 1 << i  # 避免在循环中反复计算 1 << i
            if or_all & bit == 0:  # 优化：or_all 中是 0 但 s 中是 1 的 f[s] 后面容斥用不到，无需计算
                continue
            s = 0
            while s < u:
                s |= bit  # 快速跳到第 i 位是 1 的 s
                f[s] += f[s ^ bit]
                s += 1
        # 计算完毕后，f[s] 表示 nums 中的是 s 的子集的元素个数

        ans = pow2[len(nums)]  # 所有子序列的个数
        # 枚举 or 的所有子集（包括空集）
        sub = or_all
        while True:
            p2 = pow2[f[sub]]
            ans -= -p2 if (or_all ^ sub).bit_count() % 2 else p2
            if sub == 0:
                break
            sub = (sub - 1) & or_all
        return ans % MOD
