# TC:O(nlgU) U為做快速冪的數字大小 SC:O(n)
MOD = 10
MX = 100_000

f = [0] * (MX + 1)
inv_f = [0] * (MX + 1)
p2 = [0] * (MX + 1)
p5 = [0] * (MX + 1)

f[0] = 1
for i in range(1, MX + 1):
    x = i
    # 计算 2 的幂次
    #e2 = (x & -x).bit_length() - 1
    e2 = 0
    while x % 2 == 0:
        e2 += 1
        x //= 2
    # x >>= e2
    # 计算 5 的幂次
    e5 = 0
    while x % 5 == 0:
        e5 += 1
        x //= 5
    f[i] = f[i - 1] * x % MOD
    p2[i] = p2[i - 1] + e2
    p5[i] = p5[i - 1] + e5

inv_f[MX] = pow(f[MX], 3, MOD)  # 欧拉定理求逆元
for i in range(MX, 0, -1):
    x = i
    while x % 2 == 0:
        x //= 2
    while x % 5 == 0:
        x //= 5
    inv_f[i - 1] = inv_f[i] * x % MOD

def comb(n: int, k: int) -> int:
    return f[n] * inv_f[k] * inv_f[n - k] * \
        pow(2, p2[n] - p2[k] - p2[n - k], MOD) * \
        pow(5, p5[n] - p5[k] - p5[n - k], MOD) % MOD

class Solution:
    def solve(self, s: List[int]) -> int:
        return sum(comb(len(s) - 1, i) * x for i, x in enumerate(s)) % MOD

    def hasSameDigits(self, s: str) -> bool:
        s = list(map(int, s))
        return self.solve(s[:-1]) == self.solve(s[1:])