# TC:O(n) SC:O(n)
class Solution:
    def minCost(self, s: str, encCost: int, flatCost: int) -> int:
        n = len(s)
        pre = list(accumulate(map(int, s), initial = 0))
        
        def dp(l:int, r:int) -> int:
            length = r - l
            k = pre[r] - pre[l]
            cost = flatCost if k == 0 else length * k * encCost
            if length % 2 == 0:
                m = (l + r) // 2
                cost = min(cost, dp(l, m) + dp(m, r))
            return cost
        return dp(0, n)
