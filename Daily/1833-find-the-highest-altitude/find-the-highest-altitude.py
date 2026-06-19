class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        cur = ans = 0
        for g in gain:
            cur += g
            ans = max(ans, cur)
        return ans