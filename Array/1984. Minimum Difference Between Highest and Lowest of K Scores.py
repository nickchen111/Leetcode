# TC:O(nlogn) SC:O(1)
class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        ans = inf
        for i in range(k - 1, n):
            ans = min(ans, nums[i] - nums[i - k + 1])
        return ans
