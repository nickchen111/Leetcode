class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        target = max(nums)
        i = ans = 0
        while i < n:
            j = i + 1
            if nums[i] == target:
                while j < n and nums[j] == target:
                    j += 1
            ans = max(ans, j - i)
            i = j
        return ans