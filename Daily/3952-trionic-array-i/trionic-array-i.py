class Solution:
    def isTrionic(self, nums: List[int]) -> bool:
        if nums[0] >= nums[1]:
            return False
        cnt = 1
        for i in range(2, len(nums)):
            if nums[i] == nums[i - 1]:
                return False
            if (nums[i - 2] < nums[i - 1]) != (nums[i - 1] < nums[i]):
                cnt += 1
        return cnt == 3
