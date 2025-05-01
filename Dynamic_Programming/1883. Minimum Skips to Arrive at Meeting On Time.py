# TC:O(n * n ) SC:O(n)
class Solution:
    def minSkips(self, dist: List[int], speed: int, hoursBefore: int) -> int:
        '''
        按照題目給的規則 一定要走整數時間的話 問說最少需要pass幾次 能夠在時限內走到終點?
        如果pass當下可以不用等到下一個整點走，需要求最少次數 這個好像可以直接loop 求 或者二分
        有浮點數 難搞 可以用以下技巧規避
        1. total // speed <= hoursBefore
        total <= speed * hoursBefore
        至於total 裡面哪些有用就要歸類到子問題討論
        2. 用 dfs(i - 1, j - 1) + (dist[j] // speed) <= hoursBefore
        -> 
        '''
        if sum(dist) > speed * hoursBefore:
            return -1
        n = len(dist)
        #lo, hi = 0, len(dist)
        # 空間優化
        f = [0] * (n) # 有多少次機會走到j位置時可以達到的最小cost
        for i in count(0):
            pre = 0
            for j, d in enumerate(dist[:-1]):
                f_tmp = f[j + 1]
                f[j + 1] = (f[j] + d + speed - 1) // speed * speed
                if i:
                    f[j + 1] = min(f[j + 1], pre + d)
                pre = f_tmp
            if f[-1] + dist[-1] <= speed * hoursBefore:
                return i
        return -1
        '''
        遞推
        f = [[0] * (n) for _ in range(n)] # 有多少次機會走到j位置時可以達到的最小cost
        for i in count(0):
            for j, d in enumerate(dist[:-1]):
                f[i][j + 1] = (f[i][j] + d + speed - 1) // speed * speed
                if i:
                    f[i][j + 1] = min(f[i][j + 1], f[i - 1][j] + d)
            if f[i][-1] + dist[-1] <= speed * hoursBefore:
                return i
        return -1
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int: #  還剩下多少次機會pass, 目前走到j位置
            if j < 0:
                return 0
            ans = (dfs(i, j - 1) + dist[j] + speed - 1) // speed * speed # 向上取整 (a + b - 1) // b
            if i:
                ans = min(ans, dfs(i - 1, j - 1) + dist[j])
            return ans
        for i in count(0):
            if dfs(i, len(dist) - 2) + dist[-1] <= speed * hoursBefore:
                return i
        '''
        '''
        二分 反而慢一點 因為會走很多次重疊或者不必要的太大的狀態 所以在當下的測試用例反而比較慢
        while lo < hi:
            mid = (lo + hi) // 2
            if dfs(mid, len(dist) - 2) + dist[-1] <= speed * hoursBefore:
                hi = mid
            else: 
                lo = mid + 1
        return lo
        '''
      
