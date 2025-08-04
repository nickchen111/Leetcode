min = lambda a, b: a if a < b else b
class Solution:
    def minRemoval(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        ans = n
        for i in range(n):
            max_val = nums[i] * k
            j = bisect_right(nums, max_val)
            keep = j - i
            ans = min(ans, n - keep)
        return ans
