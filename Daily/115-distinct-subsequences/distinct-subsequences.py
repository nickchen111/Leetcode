class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        m, n = len(s), len(t)
        if m < n:
            return 0
        @cache
        def dfs(i:int, j:int) -> int:
            if j == n:
                return 1
            if i == m:
                return 0
            ret = dfs(i + 1, j) # 不選
            if s[i] == t[j]:
                ret += dfs(i + 1, j + 1)
            return ret
        return dfs(0, 0)
