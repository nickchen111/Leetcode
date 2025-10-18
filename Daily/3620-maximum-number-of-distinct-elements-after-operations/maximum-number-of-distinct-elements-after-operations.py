class Solution:
    def maxDistinctElements(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums.sort()
        mn = -inf
        ans = 0
        for x in nums:
            x = min(x + k, max(mn + 1, x - k))
            ans += 1 if mn != x else 0
            mn = x
        return ans