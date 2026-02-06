class Solution:
    def minRemoval(self, nums: List[int], k: int) -> int:
        nums.sort()
        ans = n = len(nums)
        i = j = 0
        while j < n:
            while nums[j] > nums[i] * k:
                i += 1
            ans = min(ans, n - (j - i + 1))
            j += 1
        return ans