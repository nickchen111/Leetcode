# TC:O(n) SC:O(1)
class Solution:
    def maxScore(self, a: List[int], b: List[int]) -> int:
        '''
        選四個數字 讓我想到每個數字都有選or不選的可能 並且以當下狀態來說 還會有選到第幾個數字的狀態
        f[i][j] 走到 i的時候 前面已經選了k個 目前這個數字選or不選的所對應的最大值是多少
        f[i][j+1] 選的時候 = f[i-1][j] + a[j] * b[i]
        f[i][j] = f[i-1][j] 不選的話
        '''
        n = len(b)
        # 空間優化
        f = [0] + [-inf] * 4
        for i in range(n):
            prev = 0
            for j in range(4):
                prevv = f[j+1]
                f[j+1] = max(f[j+1], prev + a[j] * b[i])
                prev = prevv
        return f[4]
        '''
        遞推
        f = [[0] * 5 for _ in range(n+1)]
        f[0][1:] = [-inf] * 4
        for i in range(n):
            for j in range(4):
                f[i+1][j+1] = max(f[i][j+1], f[i][j] + a[j] * b[i])
        return f[n][4]
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int:
            if j < 0:
                return 0 # 代表選完了
            if i < 0:
                return -inf
            return  max(dfs(i - 1, j), dfs(i - 1, j - 1) + a[j] * b[i])
        return dfs(n-1, 3)
        '''
