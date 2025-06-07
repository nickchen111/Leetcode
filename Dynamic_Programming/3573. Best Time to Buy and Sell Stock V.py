# TC:O(n * k * state) state = 3 SC:O(n * k)  空間優化後可以壓在O(k * state)
class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        '''
        可以做空或者做多 問說最大收益 最多k次交易
        '''
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
        @cache
        def dfs(i:int, cnt:int, op:int) -> int: # op: 0 之前沒買 1:之前做多, 2: 之前做多
            if cnt == k:
                return 0 if op == 0 else -inf
            if i == n:
                return 0 if op == 0 else -inf
            # 不選
            ans = dfs(i + 1, cnt, op)
            # 選
            if op == 0:
                # 可以選擇現在要做多 or 做空
                ans = max(ans, dfs(i + 1, cnt, 1) - prices[i], dfs(i + 1, cnt, 2) + prices[i])
            elif op == 1: # 現在可以選擇賣出
                ans = max(ans, dfs(i + 1, cnt + 1, 0) + prices[i])
            else:
                ans = max(ans, dfs(i + 1, cnt + 1, 0) - prices[i])
            return ans
        dfs.cache_clear()
        return dfs(0, 0, 0)
            
