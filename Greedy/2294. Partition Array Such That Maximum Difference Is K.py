# TC:O(nlgn) SC:O(1)
class Solution:
    def partitionArray(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        i = ans = 0
        while i < n:
            j = i + 1
            while j < n and nums[j] - nums[i] <= k:
                j += 1
            ans += 1
            i = j
        return ans
