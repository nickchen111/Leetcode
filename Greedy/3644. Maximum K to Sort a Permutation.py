# TC:O(n) SC:O(1)
class Solution:
    def sortPermutation(self, nums: List[int]) -> int:
        if nums[0] != 0:
            return 0
        n = len(nums)
        ans = -1
        for i in range(n):
            if i != nums[i]:
                ans &= nums[i]
        return max(ans, 0)
