# TC:O(n) SC:O(1)
class Solution:
    def scoreDifference(self, nums: List[int]) -> int:
        ans = 0
        flag = 1
        for i, x in enumerate(nums):
            if ((i + 1) % 6 == 0):
                flag *= -1
            if x % 2:
                flag *= -1
            ans += x * flag
        return ans
                
