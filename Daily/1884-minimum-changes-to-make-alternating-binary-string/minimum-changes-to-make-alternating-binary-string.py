class Solution:
    def minOperations(self, s: str) -> int:
        s = list(map(int, s))
        ans = 0
        for i, x in enumerate(s):
            if x & 1 != 0 ^ (i % 2):
                ans += 1
        return min(ans, len(s) - ans)
