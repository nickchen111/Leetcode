# TC:O(1) SC:O(1)
class Solution:
    def coloredCells(self, n: int) -> int:
        return 1 + n * (n-1) * 2

class Solution:
    def coloredCells(self, n: int) -> int:
        # 1, 5, 13 -> 4, 8, 12, 16?
        # f[i] = f[i-1] + n-1 * 4
        f = [1] * (n+1)
        for i in range(1,n):
            f[i+1] = f[i] + i * 4
        return f[n]
