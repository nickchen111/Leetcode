# TC:O(n * k * m * (m + lgm)) SC:O(n * k * m) 可以空間壓縮
class Solution:
    def numOfArrays(self, n: int, m: int, k: int) -> int:
        '''
        cost == k 代表要找的最大值前面要有k-1個比他小的 後面只能比他小
        arr[i] 的數值只能到m 然後有n個
        所以可以推論說目前的最大值是啥，現在要選的數字是啥，目前花了多少cost, 當cost == k時後面的數字就有限制只能從1 ~當前最大數字
        mx, cost, 選了多少個數字i 100 * 50 * 50 * 1 ~ 100
        '''
        MOD = 10 ** 9 + 7
        # 遞推
        f = [[[0] * (m + 1) for _ in range(k+1)] for _ in range(n)] # 走到i 付出了多少cost 目前選了 1 ~ m 能有的方案數
        for t in range(1, m + 1):
            f[0][1][t] = 1
        for i in range(1, n):
            for j in range(1, min(k + 1, i + 2)): # 當下可以付出的代價
                for cur in range(1, m+1): #目前的最大值
                    f[i][j][cur] =  (sum(f[i-1][j-1][:cur]) + f[i-1][j][cur] * (cur)) % MOD
        return sum(f[-1][-1]) % MOD
        '''
        #TC:O(n * k * m * (m + lgm))
        @cache
        def dfs(i:int, cost:int, mx:int) -> int:
            # if i == n:
            #     return 1 if cost == k else 0
            if cost == k:
                return pow(mx, n - i, MOD)# 剩下 n - i個位置 可以填 1 - mx 也就是 mx ^ (n - i)
            if k - cost > n - i: # 剩下的數字沒辦法湊出cost
                return 0
            ans = 0
            for j in range(1, m + 1): # 可以填的數字
                if j > mx:
                    if cost + 1 + m - j < k:
                        break
                    else:
                        ans = (ans + dfs(i+1, cost + 1, j)) % MOD
                else:
                    ans = (ans + dfs(i + 1, cost, mx)) % MOD
            return ans
        return dfs(0, 0, 0)
        '''
