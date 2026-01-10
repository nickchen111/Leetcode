class Solution:
    def minimumDeleteSum(self, s1: str, s2: str) -> int:
        m, n = len(s1), len(s2)
        @cache
        def dfs(i, j) -> int:
            if i < 0 or j < 0:
                return sum(ord(s2[ch]) for ch in range(j+1)) + sum(ord(s1[ch]) for ch in range(i+1))
            
            return dfs(i - 1, j - 1) if s1[i] == s2[j] else min(dfs(i - 1, j) + ord(s1[i]), dfs(i, j - 1) + ord(s2[j]))
        return dfs(m - 1, n - 1)