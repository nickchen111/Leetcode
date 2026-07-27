class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        mx = mx2 = -inf
        for x in nums:
            if x >= mx:
                mx, mx2 = x, mx
            elif x > mx2:
                mx2 = x
        return (mx - 1) * (mx2 - 1)