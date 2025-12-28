# TC:O(n) SC:O(1)
class Solution:
    def maximumScore(self, nums: List[int]) -> int:
        ans = -inf
        pre_sum = sum(nums)
        suf_min = inf
        for i in range(len(nums) - 1, 0, -1):
            pre_sum -= nums[i]
            suf_min = min(suf_min, nums[i])
            ans = max(ans, pre_sum - suf_min)
        return ans
