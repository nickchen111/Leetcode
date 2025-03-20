# TC:O(m * m * n * target) ->  TC:O(m * n * target) SC:O(m*n*target)
class Solution:
    def minCost(self, houses: List[int], cost: List[List[int]], m: int, n: int, target: int) -> int:
        f = [[[inf] * (n+1) for _ in range(target + 1)] for _ in range(m+1)]
        f[0][0][0] = 0
        # 時間優化 
        for i in range(m): # 走到哪棟房子
            if houses[i] != 0:
                for j in range(0, min(target,i+1) + 1): # 前面可能有幾組 + 我這組
                    for k in range(n + 1):
                        if f[i][j][k] != inf:
                            new_group = j + (1 if houses[i] != k else 0)
                            if new_group <= target:
                                f[i+1][new_group][houses[i]] = min(f[i+1][new_group][houses[i]], f[i][j][k])
            else:
                for j in range(0, min(target,i+1) + 1): # 前面可能有幾組 + 我這組 or 不加我這組
                    mn1, mn2, c1, c2 = inf, inf, 0, 0
                    # 後面再做的就是從之前不同的顏色中選最小跟次小的出來 :)
                    for t in range(0, n + 1): # 現在選的顏色跟之前一樣
                        if t != 0:
                            f[i+1][j][t] = min(f[i+1][j][t], f[i][j][t] + cost[i][t-1])
                        if f[i][j][t] <= mn1:
                            mn2, mn1 = mn1, f[i][j][t]
                            c1, c2 = t, c1
                        elif f[i][j][t] < mn2:
                            c2 = t
                            mn2 = f[i][j][t]
                    if j + 1 <= target:
                        for t in range(1, n+1):
                            if t != c1: f[i+1][j+1][t] = mn1 + cost[i][t-1] if mn1 + cost[i][t-1] < f[i+1][j+1][t] else f[i+1][j+1][t]
                            else: f[i+1][j+1][t] = mn2 + cost[i][t-1] if mn2 + cost[i][t-1] < f[i+1][j+1][t] else f[i+1][j+1][t]
        ans = min(f[m][target][i] for i in range(1, n+1))
        return ans if ans != inf else -1

        '''
        遞推
        for i in range(m): # 走到哪棟房子
            if houses[i] != 0:
                for j in range(0, min(target,i+1) + 1): # 前面可能有幾組 + 我這組
                    for k in range(n + 1):
                        if f[i][j][k] != inf:
                            new_group = j + (1 if houses[i] != k else 0)
                            if new_group <= target:
                                f[i+1][new_group][houses[i]] = min(f[i+1][new_group][houses[i]], f[i][j][k])
            else:
                for j in range(0, min(target,i+1) + 1): # 前面可能有幾組 + 我這組
                    for k in range(n + 1):
                        if f[i][j][k] == inf: continue
                        for t in range(1, n + 1):
                            new_group = j + (1 if k != t else 0)
                            if new_group <= target:
                                f[i+1][new_group][t] = min(f[i+1][new_group][t], f[i][j][k] + cost[i][t-1])
        ans = min(f[m][target][i] for i in range(1, n+1))
        return ans if ans != inf else -1
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, j:int, k:int): # painting house, groups, prev color
            if i < 0 and j == target:
                return 0
            if j > target or i < 0:
                return inf
            ans = inf
            if houses[i] != 0:
                ans = dfs(i-1, j + (1 if houses[i] != k else 0), houses[i])
            else:
                for t in range(n):
                    ans = min(ans, dfs(i-1, j + (1 if t+1 != k else 0), t+1) + cost[i][t])
            return ans
        ret = dfs(m-1, 0, 0)
        return ret if ret != inf else -1
        '''
