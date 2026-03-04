class Solution:
    def minCost(self, n: int) -> int:
        return n * (n - 1) // 2 # 這個是從完全圖(每個點都與另一點聯通一條線) 推導出來的 等價轉換 一種組合意義上的解釋
        @cache
        def dfs(num:int) -> int:
            if num == 1:
                return 0
            ans = inf
            for i in range(1, num // 2 + 1):
                ans = min(ans, dfs(i) + dfs(num - i) + i * (num - i))
            return ans
        return dfs(n)
                