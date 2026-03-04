# TC:O(logk) SC:O(1)
MOD = 10**9 + 7
inv9 = pow(9, MOD - 2, MOD) # python 可以寫 -1 等價於 pow(9, -1, MOD)
class Solution:
    def sumOfNumbers(self, l: int, r: int, k: int) -> int:
        n = r - l + 1
        S = (l + r) * n // 2
        S %= MOD
        n_pow = pow(n, k - 1, MOD)
        repunit = (pow(10, k, MOD) - 1) * inv9 % MOD
        
        return S * n_pow % MOD * repunit % MOD
