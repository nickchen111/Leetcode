# 不排序: TC:O(n) SC:O(n) 排序 + 二分 : TC:O(mlgm) SC:O(m) m = 3 * 1e3,n = 1e5
class Solution:
    def maxTaxiEarnings(self, n: int, rides: List[List[int]]) -> int:
        # 當數據很大的話需排序來做 
        rides.sort(key=lambda x:x[1]) # sort by ending point
        drop_offs = [ride[1] for ride in rides] #用來二分
        dp = [0] * (len(rides) + 1)
        for i in range(1, len(rides) + 1):
            start, end, tip = rides[i-1]
            j = bisect_right(drop_offs, start)
            dp[i] = max(dp[i-1], dp[j] + end - start + tip)
        return dp[-1]
        '''
        f = [0] * (n + 1) # from 1 to n
        roads = [[] for _ in range(n + 1)]
        for st, end, tip in rides:
            roads[end].append((st, tip))
        for r, g in enumerate(roads): # 目前的終點 以及當下的點是否可以載客到目的地
            f[r] = f[r-1] # 在數據範圍1e5內的可以用這個避免排序or二分
            for st, tip in g:
                if f[st] + (r - st + tip) > f[r]:
                    f[r] = f[st] + (r  - st + tip)
        return f[n]
        '''
