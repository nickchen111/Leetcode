# TC:O(n) SC:O(1)
class Solution:
    def checkOnesSegment(self, s: str) -> bool:
        return "01" not in s
