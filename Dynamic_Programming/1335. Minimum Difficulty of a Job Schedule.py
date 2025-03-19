# TC:O(n*d) SC:O(n*d) 可在空間壓縮到O(n)
class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        n = len(jobDifficulty)
        if n < d: return -1
        # 單調棧優化
        f = [[inf] * n for _ in range(d)]
        f[0] = list(accumulate(jobDifficulty, max))
        for i in range(1, d):
            st = [] # stack
            for j in range(i, n):
                mn = f[i-1][j-1]
                while st and jobDifficulty[st[-1][0]] <= jobDifficulty[j]:
                   mn = min(mn, st.pop()[1])
                f[i][j] = mn + jobDifficulty[j] # 以他為最大值的狀況
                if st: # 如果還有剩 那他就有可能是被之前包含的狀況會更小 
                    f[i][j] = min(f[i][j], f[i][st[-1][0]])
                st.append((j, mn))
        return f[d-1][n-1]

        '''
        # 空間優化 該種定義方式才這麼容易做到
        f = list(accumulate(jobDifficulty, max))
        for i in range(1, d):
             # 這裡可以從值域去想 當下的數值想發揮影響只有在他是當前最大值的狀況下
             # 並且如果他走在以他為最大的數值內 他需要去找到最小的 切割點 就會是包含他為最大值的狀況下的最佳切割策略
            for j in range(n-1, i-1, -1):
                f[j] = inf
                mx = 0
                for k in range(j, i - 1, -1):
                    if jobDifficulty[k] > mx: mx = jobDifficulty[k]
                    if f[k - 1] + mx < f[j]: f[j] = f[k - 1] + mx
        return f[-1]
        '''
        '''
        遞推
        f = [[inf] * n for _ in range(d)]
        f[0] = list(accumulate(jobDifficulty, max))
        for i in range(1, d):
            for j in range(i, n):
                mx = 0
                for k in range(j, i - 1, -1):
                    if mx < jobDifficulty[k]: mx = jobDifficulty[k]
                    if f[i - 1][k - 1] + mx < f[i][j]: f[i][j] = f[i - 1][k - 1] + mx
        return f[-1][-1]
        '''

        '''
        遞歸
        @cache
        def dfs(cnt:int, i:int) -> int:
            if cnt == 0:
                return max(jobDifficulty[:i+1])
            
            mx, ans = 0, inf
            for j in range(i, cnt-1, -1):
                if jobDifficulty[j] > mx:
                    mx = jobDifficulty[j]
                tmp = mx + dfs(cnt-1, j-1)
                if tmp < ans:
                    ans = tmp
            return ans
        return dfs(d-1, n-1)
        '''
        

# 不同思考方向 就走不到 單調棧與空間優化
class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        n = len(jobDifficulty)
        if n < d: return -1
        
        f = [[inf] * n for _ in range(d)]
        f[0] = list(accumulate(jobDifficulty, max))
        for i in range(1, d):
            for j in range(i, n):
                mx = 0
                for k in range(j, i - 1, -1):
                    mx = max(mx, jobDifficulty[k])
                    f[i][j] = min(f[i][j], f[i - 1][k - 1] + mx)
        return f[-1][-1]

        '''
        遞推
        @cache
        def dfs(i:int, cnt:int) -> int:
            if cnt == 0:
                return max(jobDifficulty[:i+1])
            
            mx, ans = 0, inf
            for j in range(i, cnt-1, -1):
                if jobDifficulty[j] > mx:
                    mx = jobDifficulty[j]
                tmp = mx + dfs(j-1, cnt-1)
                if tmp < ans:
                    ans = tmp
            return ans
        return dfs(n-1, d-1)
        '''
        
