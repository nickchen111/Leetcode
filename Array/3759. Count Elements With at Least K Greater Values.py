# TC:O(nlogn) SC:O(1)
class Solution:
    def countElements(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if k == 0:
            return n
        nums.sort()
        return bisect_left(nums, nums[-k])
