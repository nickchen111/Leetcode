# TC:O(lgn) SC:O(1)
class Solution(object):
    def maximumCount(self, nums):
        neg = bisect.bisect_left(nums, 0)
        pos = len(nums) - bisect.bisect_right(nums, 0)
        return max(neg, pos)
