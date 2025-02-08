class Solution:
    def minimumDeleteSum(self, s1: str, s2: str) -> int:
        m, n = len(s1), len(s2)
        dp = [0] * (n + 1)
        for j in range(n):
            dp[j + 1] = dp[j] + ord(s2[j])

        for i, x in enumerate(s1):
            prev = dp[0]
            dp[0] += ord(x)
            for j, y in enumerate(s2):
                tmp = dp[j + 1]
                dp[j + 1] = prev if x == y else min(dp[j] + ord(y), dp[j + 1] + ord(x))
                prev = tmp
        return dp[n]

        """
        遞歸二維
        dp = [[float('inf')] * (n+1) for _ in range(m+1)]
        dp[0][0] = 0
        for i in range(m):
            dp[i+1][0] = dp[i][0] + ord(s1[i])
        for i in range(n):
            dp[0][i+1] = dp[0][i] + ord(s2[i])
        for i,x in enumerate(s1):
            for j,y in enumerate(s2):
                dp[i+1][j+1] = dp[i][j] if x == y else min(dp[i+1][j] + ord(s2[j]), dp[i][j+1] + ord(s1[i]))
        return dp[m][n]
        """
        """
        遞推
        @cache
        def dfs(i, j) -> int:
            if i < 0 and j < 0:
                return 0
            if i < 0:
                return sum(ord(s2[ch]) for ch in range(j+1))
            if j < 0:
                return sum(ord(s1[ch]) for ch in range(i+1))

            if s1[i] == s2[j]:
                return dfs(i - 1, j - 1)
            else:
                return min(dfs(i - 1, j) + ord(s1[i]), dfs(i, j - 1) + ord(s2[j]))

        return dfs(m - 1, n - 1)
        """
