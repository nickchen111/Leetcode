# TC:O(1) SC:O(1)
class Solution:
    def countOdds(self, low: int, high: int) -> int:
        return (high - low + 2) // 2 if low % 2 else (high - low + 1) // 2
