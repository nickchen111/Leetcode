# TC:O(n) SC:O(n)
min = lambda a, b : a if a < b else b
class Solution:
    def splitArray(self, nums: List[int]) -> int:
        '''
        分割兩段 左邊遞增右邊遞減
        要如何分讓兩邊差越小越好
        '''
        n = len(nums)
        right = [inf] * (n)
        right[-1] = tot = nums[-1]
        for i in range(n - 2, -1, -1):
            if nums[i] > nums[i + 1]:
                tot += nums[i]
            else:
                break
            right[i] = tot
        tot = nums[0]
        ans = inf
        for i in range(1, n):
            if right[i] != inf:
                ans = min(ans, abs(tot - right[i]))
            if nums[i] > nums[i - 1]:
                tot += nums[i]
            else:
                break
        return ans if ans != inf else -1
            
