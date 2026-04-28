class Solution:
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        nums = [x for i, row in enumerate(grid) for x in row]
        nums.sort()
        mid = len(nums) // 2
        ans = abs(nums[0] - nums[mid]) // x
        for i in range(1, len(nums)):
            if (nums[i] - nums[i - 1]) % x:
                return -1
            ans += abs(nums[i] - nums[mid]) // x
        return ans