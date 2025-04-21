# TC:O(n) SC:O(1)
class Solution:
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:
        min_s = min(accumulate(differences, initial=0))
        max_s = max(accumulate(differences, initial=0))
        return max(upper - lower - max_s + min_s + 1, 0)
