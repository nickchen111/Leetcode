# TC:O(nlogn) SC:O(1)
class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(n):
            nums[i] = abs(nums[i])
        nums.sort()
        i = 0
        j = n - 1
        ans = 0
        while i < j:
            ans += nums[j] * nums[j]
            ans -= nums[i] * nums[i]
            i += 1
            j -= 1
        if n % 2:
            ans += nums[i] * nums[i]
        return ans
