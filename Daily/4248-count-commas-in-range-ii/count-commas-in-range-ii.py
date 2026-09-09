class Solution:
    def countCommas(self, n: int) -> int:
        ans = 0
        low = 1000
        while low <= n:
            ans += n - low + 1
            low *= 1000
        return ans