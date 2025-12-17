class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        n = len(prices)
        dp = [[[-inf] * 3 for _ in range(k + 1)] for _ in range(n + 1)]
        dp[0][0][0] = 0
        for i in range(n):
            for cnt in range(k + 1):
                for op in range(3):
                    cur = dp[i][cnt][op]
                    if cur == -inf:
                        continue
                    dp[i + 1][cnt][op] = max(dp[i + 1][cnt][op], cur)
                    if op == 0 and cnt <= k:
                        dp[i + 1][cnt][1] = max(dp[i + 1][cnt][1], cur - prices[i])
                        dp[i + 1][cnt][2] = max(dp[i + 1][cnt][2], cur + prices[i])
                    elif op == 1 and cnt + 1 <= k:
                        dp[i + 1][cnt + 1][0] = max(dp[i + 1][cnt + 1][0], cur + prices[i])
                    elif op == 2 and cnt + 1 <= k:
                        dp[i + 1][cnt + 1][0] = max(dp[i + 1][cnt + 1][0], cur - prices[i])
        return max(dp[n][cnt][0] for cnt in range(k + 1))