# 最佳寫法 TC:O(n^2) SC:O(1)
min = lambda a, b : a if a < b else b
class Solution:
    def minimumTotal(self, f: List[List[int]]) -> int:
        for i in range(len(f) - 2, -1, -1):
            for j in range(i + 1):
                f[i][j] += min(f[i + 1][j], f[i + 1][j + 1])
        return f[0][0]


        '''
        遞推
        n = len(triangle)
        f = [[0] * (i + 1) for i in range(n)]
        f[-1] = triangle[-1]
        for i in range(n - 2, -1, -1):
            for j, x in enumerate(triangle[i]):
                f[i][j] = min(f[i + 1][j], f[i + 1][j + 1]) + x
        return f[0][0]
        '''
        '''
        遞歸
        n = len(triangle)
        @cache
        def dfs(i: int, j: int) -> int:
            if i == n - 1:
                return triangle[i][j]
            return min(dfs(i + 1, j), dfs(i + 1, j + 1)) + triangle[i][j]
        return dfs(0, 0)
        '''

# 將arrary內數值當作是下一行的參考dp寫法  TC:O(n^2) SC:O(n)
min = lambda a, b : a if a < b else b
class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        dp = [inf] * n
        dp[0] = triangle[0][0]
        for i in range(1, n):
            tmp = [inf] * n
            m = len(triangle[i])
            for j in range(m - 1):
                tmp[j] = min(tmp[j], dp[j] + triangle[i][j])
                tmp[j + 1] = min(tmp[j + 1], dp[j] + triangle[i][j + 1])
            dp = tmp
        # print(dp)
        ans = inf
        for i in range(n):
            ans = min(ans, dp[i])
        return ans
