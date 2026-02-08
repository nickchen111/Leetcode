class Solution:
    def dominantIndices(self, nums: List[int]) -> int:
        tot = sum(nums)
        ans = 0
        n = len(nums)
        for i in range(n - 1):
            if nums[i] > (tot - nums[i]) // (n - i - 1):
                ans += 1
            tot -= nums[i]
        return ans