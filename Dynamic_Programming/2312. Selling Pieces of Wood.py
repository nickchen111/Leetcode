# TC:O(m * n * (m + n)) SC:O(m * n)
class Solution:
    def sellingWood(self, m: int, n: int, prices: List[List[int]]) -> int:
        '''
        給你一大塊矩形，還有每個小塊矩形可以賣的價格 問你最多可以賣到多少錢
        m = n = 200,
        p.size() = 1e4
        price <= 1e6
        以遞歸角度出發 我會想到當下這塊地我可以怎麼賣? 賣完還會剩下多少?然後再根據現有狀況
        1e4中找一些賣掉，這裡賣地 想到兩個可能可以做的優化
        1. 按照地的price / 地面積 去計算cp值 越高越好 可能會優先用
        2. 先按照地的高度做排序，如果一樣排寬 這樣之後判斷要用哪塊可以二分嘗試
        我的想法是divide and conquer 一旦選了 就拆成上下兩部分 如果高度到頂的話 就不拆
        這個想法錯誤在 沒辦法包含 我不管這個高or寬是否有可以賣的剛好高寬 我就先切，進而忽略了切中間的可能性 導致我的答案不會是最優的....
        '''
        # 只需取一半就好 有對稱性
        f = [[0] * (n + 1) for _ in range(m + 1)]
        for h, w, p in prices:
            f[h][w] = p
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                # f[i][j] = price_map.get((i,j), 0)
                for k in range(1, i // 2 + 1):
                    f[i][j] = max(f[i][j], f[i - k][j] + f[k][j])
                for k in range(1, j // 2 + 1):
                    f[i][j] = max(f[i][j], f[i][j - k] + f[i][k])
        return f[m][n]
        '''
        遞推 也順便把 map優化掉
        #price_map = {(h, w): p for h, w, p in prices}
        f = [[0] * (n + 1) for _ in range(m + 1)]
        for h, w, p in prices:
            f[h][w] = p
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                # f[i][j] = price_map.get((i,j), 0)
                for k in range(1, i):
                    f[i][j] = max(f[i][j], f[i - k][j] + f[k][j])
                for k in range(1, j):
                    f[i][j] = max(f[i][j], f[i][j - k] + f[i][k])
        return f[m][n]
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int:
            if i == 0 or j == 0:
                return 0
            ans = price_map.get((i,j), 0)
            
            for k in range(1, i):
                ans = max(ans, dfs(k, j) + dfs(i - k, j))
            for k in range(1, j):
                ans = max(ans, dfs(i, k) + dfs(i, j - k))
            return ans
        return dfs(m, n)
        '''


