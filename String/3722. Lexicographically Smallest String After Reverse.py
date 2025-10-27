# TC:O(n^2) SC:O(n)
class Solution:
    def lexSmallest(self, s: str) -> str:
        n = len(s)
        ans = 'z' * n
        for k in range(1, n + 1):
            ans = min(ans, s[:k][::-1] + s[k:n], s[:k] + s[k:][::-1])
        return ans
