# TC:O(n ^3 + n * n * k) SC:O(n * n + n * k)
class Solution:
    def minDistance(self, houses: List[int], k: int) -> int:
        '''
        首先根據中位數定理 mailbox一定插在任意兩個家之間或者如果很夠我就單獨放這個家上面 那我就去嘗試各種不同插法
        x  x   x   x 
        '''
        houses.sort()
        n = len(houses)
        dis = [[inf] * n for _ in range(n)]
        for i in range(n):
            for j in range(i,n):
                m = (i + j) >> 1
                d = 0
                for t in range(i, j + 1):
                    d += abs(houses[t] - houses[m])
                dis[i][j] = d
        f = [[inf] * (k+1) for _ in range(n+1)]
        for i in range(n):
            for j in range(min(i+1, k)): # 代表目前houses[i:j+1] 為一組 之前還可以用多少個mailbox
                f[0][j] = 0
                for t in range(i, -1, -1):
                    if dis[t][i] + f[t][j] < f[i+1][j+1]:
                        f[i+1][j+1] = dis[t][i] + f[t][j]
        return f[n][k]

        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0:
                return 0
            if j == 0: # 還剩下家沒有分 但是已經沒有郵筒了
                return inf
            ans = dfs(i - 1, j - 1)
            # 這裡要怎麼快速判斷 總和距離是多少 -> 先做預處理
            for t in range(i-1, -1, -1):
                tmp = dfs(t - 1, j - 1)
                if tmp + dis[t][i] < ans:
                    ans = tmp + dis[t][i]
            return ans
        return dfs(n-1, k)
        '''
