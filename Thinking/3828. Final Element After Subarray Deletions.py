# TC:O(1) SC:O(1)
class Solution:
    def finalElement(self, nums: List[int]) -> int:
        return max(nums[0], nums[-1])
