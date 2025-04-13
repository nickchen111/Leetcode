# TC:O(lgn) SC:O(lgn) n = 10^15 -> lgn ~= 50
class Solution:
    def countGoodNumbers(self, n: int) -> int:
        MOD = 10**9 + 7
        # 有 (n + 1) // 2 個偶數位（包含第 0 位）
        even_count = (n + 1) // 2
        odd_count = n // 2
        return pow(5, even_count, MOD) * pow(4, odd_count, MOD) % MOD
