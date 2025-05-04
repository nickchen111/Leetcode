# TC:O(n * k * n * k) SC:O(n * n * k)
class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        '''
        可以選k個相鄰數字merge, merge後兩者時間相加
        15 + 40 + 6 = 61
        所以merge這件事情會讓時間變長 要盡可能短? 二分?!
        時間加總只有100 感覺有可能是 n * m ?!
        n <= 50, k <= 10
        用or不用 用了以後他的時間變成啥?
        n * k * n = 50 * 10 * 50 ~= 1e5
        但是沒考量到重複merge的狀況
        '''
        s = list(accumulate(time, initial=0))
        f = [[[inf] * n for _ in range(n)] for _ in range(k + 1)]
        f[0][-1] = [0] * n
        for left_k in range(k+1):
            for i in range(n-2, -1, -1):
                for pre in range(i+1):
                    t = s[i + 1] - s[pre]
                    f[left_k][i][pre] = min(f[left_k - (nxt - i - 1)][nxt][i + 1] + (position[nxt] - position[i]) * t
                                            for nxt in range(i + 1, min(n, i + 2 + left_k)))
        return f[k][0][0]
        '''
        遞歸
        @cache
        def dfs(i:int, j:int, pre:int) ->int:
            if i == n - 1:
                return 0 if j == 0 else inf
            tot = s[i+1] - s[pre]
            ans = inf
            for t in range(i + 1, min(n, i + 2 + j)): # 要走到的位置
                ans = min(ans, dfs(t, j - (t - i - 1), i + 1) + (position[t] - position[i]) * tot)
            return ans
        return dfs(0, k, 0)
        '''
        '''
        時間當參數寫法
        @cache
        def dfs(i:int, j:int, tot:int) ->int:
            if i == n - 1:
                return 0 if j == 0 else inf
            if j < 0:
                return inf
            totTime = 0
            ans = inf
            for t in range(i + 1, n): # 要走到的位置
                totTime += time[t]
                ans = min(ans, dfs(t, j - (t - i - 1), totTime) + (position[t] - position[i]) * tot)
            return ans
        return dfs(0, k, time[0])
        '''
                 
