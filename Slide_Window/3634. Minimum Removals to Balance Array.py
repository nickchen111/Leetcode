# 二分: TC:O(nlogn) SC:O(1) Sliding Window: TC:O(n) SC:O(1)
min = lambda a, b: a if a < b else b
max = lambda a, b: a if a > b else b
class Solution:
    def minRemoval(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        # ans = n
        ans = 0
        i = 0
        for j in range(n):
            while nums[i] * k < nums[j]:
                i += 1
            ans = max(ans, j - i + 1)
        return n - ans

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
