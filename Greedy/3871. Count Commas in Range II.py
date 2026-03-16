# Math TC:O(1) SC:O(1)
class Solution:
    def countCommas(self, n: int) -> int:
        k = 5
        if n < 10**15:
            k = (len(str(n)) - 1) // 3
        return k * (n + 1) - ((10 ** (k * 3 + 3)) - 1000) // 999

# 貢獻法 TC:O(logn 以1000為底) SC:O(1)
class Solution:
    def countCommas(self, n: int) -> int:
        ans = 0
        k = 1000
        while k <= n:
            ans += (n - k + 1)
            k *= 1000
        return ans
