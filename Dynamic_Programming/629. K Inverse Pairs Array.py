# TC:O(n * k) SC:O(n * k)
class Solution:
    def kInversePairs(self, n: int, k: int) -> int:
        '''
        這題要求剛好要有k個逆序對 total 問說會有多少種組合方式?
        1 ~ n 的數字
        這題如果像3193 寫一個n^3 是不行的， 要優化到n^2
        '''
        MOD = 10 ** 9 + 7
        # 空間優化
        f = [0] * (k + 1)
        f[0] = 1
        for i in range(1, n):
            pre = list(accumulate(f, initial=0))
            new_f = [0] * (k + 1)
            for j in range(min(k, i * (i + 1) // 2) + 1): # 當下可以組成多少逆序對
                mn = max(0, j - i)
                new_f[j] = (pre[j+1] - pre[mn]) % MOD
                # for t in range(0, i+1):
                #     if j >= t:
                #         f[i][j] = (f[i][j] + f[i-1][j - t]) % MOD
            f = new_f.copy()
        return f[k]
        '''
        f = [[0] * (k + 1) for _ in range(n)]
        f[0][0] = 1
        for i in range(1, n):
            pre = list(accumulate(f[i-1], initial=0))
            for j in range(min(k, i * (i + 1) // 2) + 1): # 當下可以組成多少逆序對
                mn = max(0, j - i)
                f[i][j] = (pre[j+1] - pre[mn]) % MOD
                # for t in range(0, i+1):
                #     if j >= t:
                #         f[i][j] = (f[i][j] + f[i-1][j - t]) % MOD
        return f[n-1][k]
        '''


        '''
        遞歸TLE
        @cache
        def dfs(i:int, cnt:int) -> int:
            if i == 0:
                return 1 if cnt == 0 else 0
            ans = 0
            for j in range(i + 1):
                ans = (ans + dfs(i - 1, cnt - j)) % MOD
            return ans
        return dfs(n-1, k)
        '''
