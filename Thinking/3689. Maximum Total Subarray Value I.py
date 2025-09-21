# TC:O(n) SC:O(1)
class Solution:
    def maxTotalValue(self, nums: List[int], k: int) -> int:
        return (max(nums) - min(nums)) * k
