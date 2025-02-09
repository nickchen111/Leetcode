# TC: O(m*n) SC:O(n)
class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        m, n = len(s), len(t)
        if m < n:
            return 0
        # 選 or 不選
        dp = [0] * (n + 1)
        dp[0] = 1
        for i, x in enumerate(s):
            prev = dp[0]
            for j, y in enumerate(t):
                tmp = dp[j+1]
                dp[j+1] = prev + dp[j+1] if x == y else dp[j+1]
                prev = tmp
        return dp[n]
        """
        遞推 二維
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = 1
        for i, x in enumerate(s):
            dp[i+1][0] = 1
            for j, y in enumerate(t):
                dp[i+1][j+1] = dp[i][j] + dp[i][j+1] if x == y else dp[i][j+1]
        return dp[m][n]
        """
        """
        遞歸 
        @cache
        def dfs(i, j) -> int:
            if j < 0:
                return 1
            if i < 0:
                return 0
            return dfs(i-1, j-1) + dfs(i-1,j) if s[i] == t[j] else dfs(i-1, j)
        return dfs(m-1, n-1)
        """
            
        
