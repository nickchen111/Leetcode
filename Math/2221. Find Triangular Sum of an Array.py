# TC:O(n) SC:O(1)
MOD = 10
MX = 1000
POW2 = (2, 4, 8, 6)

# 計算组合數，需要計算階乘及其逆元
f = [0] * (MX + 1)  # f[n] = n!
inv_f = [0] * (MX + 1)  # inv_f[n] = n!^-1
p2 = [0] * (MX + 1)  # n! 中的 2 的幂次
p5 = [0] * (MX + 1)  # n! 中的 5 的幂次

f[0] = inv_f[0] = 1
for i in range(1, MX + 1):
    x = i

    # 分離質因子 2，計算 2 的幂次
    e2 = (x & -x).bit_length() - 1
    x >>= e2

    # 分離質因子 5，計算 5 的幂次
    e5 = 0
    while x % 5 == 0:
        e5 += 1
        x //= 5

    f[i] = f[i - 1] * x % MOD
    inv_f[i] = pow(f[i], 3, MOD)  # 歐拉定理求逆元
    p2[i] = p2[i - 1] + e2
    p5[i] = p5[i - 1] + e5

def comb(n: int, k: int) -> int:
    e2 = p2[n] - p2[k] - p2[n - k]
    return f[n] * inv_f[k] * inv_f[n - k] * \
        (POW2[(e2 - 1) % 4] if e2 else 1) * \
        (5 if p5[n] - p5[k] - p5[n - k] else 1)

class Solution:
    def triangularSum(self, nums: List[int]) -> int:
        n = len(nums)
        return sum(comb(n - 1, i) * x for i, x in enumerate(nums)) % MOD
