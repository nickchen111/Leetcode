class Solution:
    def maxProfit(self, prices: List[int], strategy: List[int], k: int) -> int:
        n = len(prices)
        pre = list(accumulate((x * y for x, y in zip(prices, strategy)), initial = 0))
        s_sell = list(accumulate(prices, initial = 0))
        ans = max(pre[i - k] + pre[n] - pre[i] + s_sell[i] - s_sell[i - k // 2] for i in range(k, n + 1))
        return max(ans, pre[n])