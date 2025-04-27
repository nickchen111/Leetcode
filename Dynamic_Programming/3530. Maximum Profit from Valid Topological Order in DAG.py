# TC:O(n * 2 ^ n) SC:O(2 ^ n)
class Solution:
    def maxProfit(self, n: int, edges: list[list[int]], score: list[int]) -> int:
        if not edges:
            score.sort()
            return sum(s * i for i,s in enumerate(score,1))
        pre = [0] * n
        for e in edges:
            u, v = e[0], e[1]
            pre[v] |= (1 << u)
        
        N = 1 << n
        dp = [float('-inf')] * N
        dp[0] = 0
       
        for mask in range(N):
            if dp[mask] == float('-inf'):
                continue
            k = mask.bit_count()
            for i in range(n):
                if not (mask & (1 << i)) and ((mask & pre[i]) == pre[i]):
                    nxt = mask | (1 << i)
                    profit = dp[mask] + score[i] * (k + 1)
                    dp[nxt] = max(dp[nxt], profit)
       
        return dp[N - 1]
        '''
        @cache
        def dfs(s:int) -> int:
            ans = 0
            i = s.bit_count() + 1
            for j, p in enumerate(pre):
                if ((s >> j) & 1) == 0 and (s | p) == s:
                    r = dfs(s | (1 << j)) + score[j] * i
                    if r > ans:
                        ans = r
            return ans
        return dfs(0)
        '''
