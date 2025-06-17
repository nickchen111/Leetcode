# TC:O(n) SC:O(1)
class Solution:
    def maximumDifference(self, nums: List[int]) -> int:
        ans, mn = -1, nums[0]
        for i in range(1, len(nums)):
            if nums[i] > mn:
                ans = max(ans, nums[i] - mn)
            else:
                mn = min(mn, nums[i])
        return ans
