class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = True
            if i + 1 < n:
                dp[i][i + 1] = True if s[i] == s[i + 1] else False
        for i in range(n - 2, -1, -1):
            for j in range(i + 2, n):
                if s[i] == s[j] and dp[i + 1][j - 1]:
                    dp[i][j] = True
        f = [0] * (n + 1)
        for i in range(n):
            if i < k - 1:
                continue
            f[i + 1] = f[i]
            for j in range(i - k + 1, -1, -1):
                if dp[j][i]:
                    if f[i + 1] < f[j] + 1:
                        f[i + 1] = f[j] + 1
                    else:
                        break
        return f[n] 