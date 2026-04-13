# TC:O(n) SC:O(1)
class Solution:
    def getMinDistance(self, nums: List[int], target: int, start: int) -> int:
        return min(abs(i - start) for i, x in enumerate(nums) if x == target)
