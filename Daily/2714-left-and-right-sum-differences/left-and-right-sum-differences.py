class Solution:
    def leftRightDifference(self, nums: List[int]) -> List[int]:
        total = sum(nums)

        left_sum = 0
        for i, x in enumerate(nums):
            nums[i] = abs(left_sum * 2 + x - total)
            left_sum += x
        return nums