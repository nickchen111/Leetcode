# TC: O(m*n) SC:O(m*n)
class Solution:
    def shortestCommonSupersequence(self, s: str, t: str) -> str:
        m, n = len(s), len(t)
        dp = [[float('inf')] * (n+1) for _ in range(m+1)]
        dp[0][0] = 0
        for i in range(1,m+1):
            dp[i][0] = i
        for j in range(1,n+1):
            dp[0][j] = j
        for i, x in enumerate(s):
            for j, y in enumerate(t):
                dp[i+1][j+1] = dp[i][j] + 1 if x == y else min(dp[i+1][j], dp[i][j+1]) + 1
        i, j = m-1,n-1
        ans = []
        while i >= 0 and j >= 0:
            if s[i] == t[j]:
                ans.append(s[i])
                i -= 1
                j -= 1
            elif dp[i+1][j+1] == dp[i][j+1] + 1:
                ans.append(s[i])
                i -= 1
            else:
                ans.append(t[j])
                j -= 1
        return s[:i+1] + t[:j+1] + ''.join(reversed(ans))
        """
        遞歸
        @cache
        def dfs(i,j) -> int:
            if i < 0 or j < 0:
                return max(i+1, j+1)
            return dfs(i-1,j-1) + 1 if s[i] == t[j] else min(dfs(i-1,j), dfs(i, j-1)) + 1
        ans = []
        @cache
        def print_ans(i, j) -> str:
            if i < 0:
                return t[:j+1]
            if j < 0:
                return s[:i+1]
            if s[i] == t[j]:
                return print_ans(i-1,j-1) + s[i]
            if dfs(i-1,j) + 1 == dfs(i,j):
                return print_ans(i-1,j) + s[i]
            return print_ans(i,j-1) + t[j]
        return print_ans(m-1,n-1)
        """
