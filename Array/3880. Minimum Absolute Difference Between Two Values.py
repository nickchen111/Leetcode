# TC:O(n) SC:O(1)
class Solution:
    def minAbsoluteDifference(self, nums: list[int]) -> int:
        pos = [-1, -1, -1]
        ans = inf
        
        for i, x in enumerate(nums):
            if x == 1 or x == 2:
                pos[x] = i
                other_pos = pos[3 - x]
                if other_pos != -1:
                    ans = min(ans, i - other_pos)
                    
        return ans if ans != inf else -1
