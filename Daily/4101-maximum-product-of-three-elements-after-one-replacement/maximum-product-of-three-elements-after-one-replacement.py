class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        # 找出最大兩個最小1個
        mx1 = mx2 = -inf
        mn1 = mn2 = inf
        for x in nums:
            if x > mx1:
                mx2, mx1 = mx1, x
            elif x > mx2:
                mx2 = x
            if x < mn1:
                mn2, mn1 = mn1, x
            elif x < mn2:
                mn2 = x
        return max(mx1 * mx2 * 10 ** 5, mx1 * mn1 * -(10 ** 5), mn1 * mn2 * 10 ** 5)
        
