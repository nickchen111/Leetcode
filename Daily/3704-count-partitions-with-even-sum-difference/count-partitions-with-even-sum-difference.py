class Solution:
    def countPartitions(self, nums: List[int]) -> int:
        tot = sum(nums)
        cur = ans = 0
        for i in range(len(nums) - 1):
            cur += nums[i]
            tot -= nums[i]
            if (cur - tot) % 2 == 0:
                ans += 1
        return ans