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