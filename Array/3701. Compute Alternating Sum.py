# TC:O(n) SC:O(1)
class Solution:
    def alternatingSum(self, nums: List[int]) -> int:
        ans = 0
        for i in range(len(nums)):
            ans += nums[i] if i % 2 == 0 else -nums[i]
        return ans
