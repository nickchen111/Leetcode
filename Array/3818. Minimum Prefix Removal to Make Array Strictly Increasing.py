# TC:O(n) SC:O(1)
class Solution:
    def minimumPrefixLength(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(n - 2, -1, -1):
            if nums[i] >= nums[i + 1]:
                return i + 1
        return 0
        
