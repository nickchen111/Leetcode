min = lambda a, b : a if a < b else b
class Solution:
    def minimumTotal(self, f: List[List[int]]) -> int:
        for i in range(len(f) - 2, -1, -1):
            for j in range(i + 1):
                f[i][j] += min(f[i + 1][j], f[i + 1][j + 1])
        return f[0][0]