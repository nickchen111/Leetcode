# DP
class Solution:
    def longestString(self, x: int, y: int, z: int) -> int:
        @cache
        def dfs(i:int, j:int, k:int, v:int) -> int:
            if i < 0 or j < 0 or k < 0:
                return 0
            # x 打頭
            if v == 0:
                return dfs(i, j-1, k, 1) + 2
            if v == 1:
                return max(dfs(i-1, j, k, 0), dfs(i, j, k-1, 2)) + 2
            return max(dfs(i-1, j, k, 0), dfs(i, j, k-1, 2)) + 2
        return max(dfs(x-1, y, z, 0), dfs(x, y-1, z, 1), dfs(x, y, z-1, 2))

# Greedy or Thinking TC:O(1) SC:O(1)
class Solution:
    def longestString(self, x: int, y: int, z: int) -> int:
        return (min(x,y) * 2 + 1 + z) * 2 if x != y else (x * 2 + z) * 2
