# TC:O(n*m) SC:O(n)
class Solution:
    def minDistance(self, s: str, t: str) -> int:
        m, n = len(s), len(t)
        dp = [0] * (n+1)
        for j in range(n):
            dp[j+1] = j + 1
        for i, x in enumerate(s):
            prev = dp[0]
            dp[0] += 1
            for j, y in enumerate(t):
                tmp = dp[j+1]
                dp[j+1] = prev if x == y else min(prev+1, dp[j+1]+1, dp[j] + 1)
                prev = tmp
        return dp[n]
        """
        遞推二維
        dp = [[0] * (n+1) for _ in range(m+1)]
        for i in range(m):
            dp[i+1][0] = i + 1
        for j in range(n):
            dp[0][j+1] = j + 1
        for i, x in enumerate(s):
            for j, y in enumerate(t):
                dp[i+1][j+1] = dp[i][j] if x == y else min(dp[i][j]+1, dp[i][j+1]+1, dp[i+1][j] + 1)
        return dp[m][n]
        """
        """
        遞歸
        @cache 
        def dfs(i, j) -> int:
            if i < 0 and j < 0:
                return 0
            if j < 0:
                return i+1
            if i < 0:
                return j+1
            return dfs(i-1,j-1) if s[i] == t[j] else min(dfs(i-1, j-1) + 1, dfs(i-1,j) + 1, dfs(i,j-1) + 1)
        return dfs(m-1, n-1)
        """
