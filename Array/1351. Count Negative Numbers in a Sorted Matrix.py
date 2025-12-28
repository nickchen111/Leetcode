# TC:O(mn) SC:O(1)
class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        ans = 0
        for g in grid:
            n = len(g)
            for i in range(n):
                if g[i] < 0:
                    ans += n - i
                    break
        return ans
