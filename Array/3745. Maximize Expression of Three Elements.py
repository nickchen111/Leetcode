# TC:O(n) SC:O(1)
class Solution:
    def maximizeExpressionOfThree(self, nums: List[int]) -> int:
        mx1, mx2, mn = -inf, -inf, inf
        for x in nums:
            if x > mx1:
                mx1, mx2 = x, mx1
            elif x > mx2:
                mx2 = x
            mn = min(mn, x)
        return mx1 + mx2 - mn
