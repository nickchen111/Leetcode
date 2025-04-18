# TC:O(m * n * k * (m + n)) SC:O(m * n * k)
class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        '''
        這題就是要確保切的時候 左 or 上一定要有蘋果，
        可以設定一個狀態定義成 剩下多少個row, col, 還剩下幾刀要切的狀態下可以分出去的合法狀態
        50 * 50 * 10 要如何判斷切下去的地方是否有蘋果 hmmm 二維前綴和好像可以做到
        '''
        MOD = 10**9+7
        m, n = len(pizza), len(pizza[0])

        presum = [[0]*(n+1) for _ in range(m+1)]
        for i in range(m):
            for j in range(n):
                presum[i+1][j+1] = (
                    presum[i][j+1]
                    + presum[i+1][j]
                    - presum[i][j]
                    + (pizza[i][j] == 'A')
                )
        def has_apple(r1, c1, r2, c2) -> bool:
            return (
                presum[r2+1][c2+1]
                - presum[r1][c2+1]
                - presum[r2+1][c1]
                + presum[r1][c1]
            ) > 0
        dp = [[[0]*n for _ in range(m)] for _ in range(k)]
        for i in range(m-1, -1, -1):
            for j in range(n-1, -1, -1):
                dp[0][i][j] = 1 if has_apple(i, j, m-1, n-1) else 0
        for c in range(1, k):
            for i in range(m-1, -1, -1):
                for j in range(n-1, -1, -1):
                    total = 0
                    for r in range(i+1, m):
                        if has_apple(i, j, r-1, n-1):
                            total = (total + dp[c-1][r][j]) % MOD
                    for s in range(j+1, n):
                        if has_apple(i, j, m-1, s-1):
                            total = (total + dp[c-1][i][s]) % MOD
                    dp[c][i][j] = total
        return dp[k-1][0][0]
        
        '''
        遞歸 TC:O(m * n * k * (m + n))
        @cache
        def dfs(row:int, col:int, cnt:int):
            if cnt == 0:
                return 1 if has_apple(row, col, m-1, n-1) else 0
            if not has_apple(row, col, m-1, n-1):
                return 0
            
            ans = 0
            for i in range(row+1, m):
                if has_apple(row, col, i - 1, n-1):
                    ans = (ans + dfs(i, col, cnt - 1)) % MOD
            for j in range(col+1, n):
                if has_apple(row, col, m-1, j - 1):
                    ans = (ans + dfs(row, j, cnt - 1)) % MOD
            return ans
        return dfs(0, 0, k - 1)
        '''
