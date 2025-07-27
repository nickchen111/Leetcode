# TC:O(nlogn) SC:O(1)
class Solution:
    def maximumMedianSum(self, nums: List[int]) -> int:
        i = ans = 0
        j = len(nums) - 1
        nums.sort()
        while i < j:
            ans += nums[j - 1]
            i += 1
            j -= 2
        return ans
