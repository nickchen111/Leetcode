# TC:O(n) SC:O(1)
class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        '''
        可能會有幾種情況
        1. 兩種橋接再一起
        2. 一段超長的後面 or 前面補一個
        '''
        n = len(nums)
        ans = i = prev = 0
        while i < n:
            j = i
            while j + 1 < n and nums[j] <= nums[j + 1]:
                j += 1
            ans = max(ans, min(n, j - i + 2))
            if i - 1 >= 0 and i + 1 < n and nums[i - 1] <= nums[i + 1] or i - 2 >= 0 and nums[i - 2] <= nums[i]:
                ans = max(ans, min(n, prev + j - i + 1))
            prev = j - i + 1
            i = j + 1
        return ans
                
