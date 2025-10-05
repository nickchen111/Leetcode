# TC:O(n) SC:O(1)
class Solution:
    def longestSubsequence(self, nums: List[int]) -> int:
        if all(x == 0 for x in nums):
            return 0
        xor_sum = reduce(xor, nums)
        return len(nums) - (xor_sum == 0)
