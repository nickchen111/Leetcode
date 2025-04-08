# TC:O(n^2) SC:O(n * k) k = 10
class Solution:
    def minimumOperations(self, grid: List[List[int]]) -> int:
        '''
        需要讓每個位置 i,j = i+1,j, != i, j+1 問說最少需要改幾次
        f[j][k] = f[j+1][k'] k != k
        '''
        m, n = len(grid), len(grid[0])
        # 先預處理每一行的元素個數from 0 - 9
        pre = [[0] * 10 for _ in range(n)]
        for i in range(m):
            for j in range(n):
                pre[j][grid[i][j]] += 1
        '''
        遞歸
        @cache
        def dfs(i:int, prev:int) -> int:
            if i < 0:
                return 0
            # 判斷這次要選啥然後所需的cost 去取最小的 並且不能跟上次的一樣
            ans = inf
            for k in range(10):
                if k != prev:
                    ans = min(ans, dfs(i-1, k) + m - pre[i][k])
            return ans
        return dfs(n-1, -1)
        '''
        f = [[inf] * 10 for _ in range(n)]
        for j in range(n-1, -1, -1):
            # 計算上一行最小的元素與次小的
            mn, mn2, num = inf, inf, -1
            if j + 1 < n:
                for k in range(10):
                    if f[j+1][k] <= mn:
                        mn, mn2, num = f[j+1][k], mn, k
                    elif f[j+1][k] < mn2: mn2 = f[j+1][k]
            if num == -1:
                for k in range(10):
                    f[j][k] = m - pre[j][k]
            else:
                for k in range(10):
                    if k != num:
                        f[j][k] = m - pre[j][k] + mn
                    else:
                        f[j][k] = m - pre[j][k] + mn2
        return min(f[0][k] for k in range(10))
        
        

