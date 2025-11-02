class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        # 找出最大兩個最小1個
        mx1 = mx2 = -inf
        for x in nums:
            x = abs(x)
            if x > mx1:
                mx2, mx1 = mx1, x
            elif x > mx2:
                mx2 = x
        return mx1 * mx2 * 10 ** 5
        
