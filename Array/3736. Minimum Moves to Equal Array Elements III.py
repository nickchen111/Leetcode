# TC:O(n) SC:O(1)
class Solution:
    def minMoves(self, nums: List[int]) -> int:
        mx = max(nums)
        ans = 0
        for x in nums:
            ans += mx - x
        return ans
