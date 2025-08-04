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
