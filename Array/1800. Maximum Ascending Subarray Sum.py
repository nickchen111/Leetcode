# TC:O(n) SC:O(1)
class Solution:
    def maxAscendingSum(self, nums: List[int]) -> int:
        sum, ans = nums[-1], nums[-1]
        for i in range(len(nums) - 2, -1, -1):
            sum = sum + nums[i] if nums[i] < nums[i+1] else nums[i]
            ans = max(ans, sum)
        return ans
