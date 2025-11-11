class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        for s in strs:
            cnt0 = cnt1 = 0
            for ch in s:
                cnt0 += 1 if ch == '0' else 0
                cnt1 += 1 if ch == '1' else 0
            if cnt0 <= m and cnt1 <= n:
                for i in range(m, cnt0 - 1, -1):
                    for j in range(n, cnt1 - 1, -1):
                        dp[i][j] = max(dp[i - cnt0][j - cnt1] + 1, dp[i][j])
        return max(dp[i][j] for i in range(m + 1) for j in range(n + 1))