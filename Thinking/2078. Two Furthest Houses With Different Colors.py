# TC:O(n) SC:O(1)
class Solution:
    def maxDistance(self, colors: List[int]) -> int:
        n = len(colors)
        c = colors[0]
        if c != colors[-1]:
            return n - 1
        l = 1
        while colors[l] == c:
            l += 1
        r = n - 2
        while colors[r] == c:
            r -= 1
        return max(r, n - l - 1)
