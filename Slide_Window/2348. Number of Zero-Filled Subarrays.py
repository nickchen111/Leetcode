# TC:O(n) SC:O(1)
class Solution:
    def zeroFilledSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        i = ans = 0
        while i < n:
            j = i 
            while j < n and nums[j] == 0:
                j += 1
                ans += j - i
            i = j + 1
        return ans
