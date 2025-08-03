# TC:O(n) SC:O(n)
class Solution:
    def maxSumTrionic(self, nums: List[int]) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + nums[i]

        incL = [-inf] * n
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                if i + 1 < n and nums[i] < nums[i + 1] and max(nums[i-1], incL[i - 1]) + nums[i] < nums[i]:
                    incL[i] = nums[i]
                else:
                    incL[i] = max(nums[i-1], incL[i - 1]) + nums[i]
        
        incR = [-inf] * n
        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                incR[i] = max(nums[i+1], incR[i + 1]) + nums[i]

        ans = -inf
        i = 1
        while i < n:
            j = i + 1
            while j < n and nums[j] < nums[j - 1]:
                j += 1
            if j - i > 1:
                ans = max(ans, incL[i] + incR[j - 1] + prefix[j] - prefix[i] - nums[i] - nums[j - 1])
            i = j
        return ans
