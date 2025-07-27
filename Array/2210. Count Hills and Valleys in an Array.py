# TC:O(n) SC:O(1)
class Solution:
    def countHillValley(self, nums: List[int]) -> int:
        n = len(nums)
        i = 1
        ans = 0
        while i < n:
            j = i + 1
            while j < n and nums[j] == nums[i]:
                j += 1
            if j < n and ((nums[i] > nums[i - 1] and nums[i] > nums[j]) or (nums[i] < nums[i - 1] and nums[i] < nums[j])):
                ans += 1
            i = j
        return ans
