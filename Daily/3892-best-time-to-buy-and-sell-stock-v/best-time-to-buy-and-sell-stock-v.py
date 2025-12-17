class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        n = len(prices)
        @cache
        def dfs(i:int, x:int, cnt:int) -> int:
            if i == n:
                return 0 if x == 0 else -inf
            if cnt == 0:
                return 0 if x == 0 else -inf
            # 之前狀態維持, 現在賣or買 看狀況決定可以做哪個操作
            ans = dfs(i + 1, x, cnt)
            if x == 0:
                ans = max(ans, dfs(i + 1, 1, cnt) - prices[i], dfs(i + 1, 2, cnt) + prices[i])
            if x == 1: # 之前是買 
                ans = max(ans, dfs(i + 1, 0, cnt - 1) + prices[i])
            else:
                ans = max(ans, dfs(i + 1, 0, cnt - 1) - prices[i])
            return ans
        ret = dfs(0, 0, k)
        dfs.cache_clear()
        return ret