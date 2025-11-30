# TC:O(n) SC:O(n)
class Solution:
    def maxDistinct(self, s: str) -> int:
        return len(set(s))
