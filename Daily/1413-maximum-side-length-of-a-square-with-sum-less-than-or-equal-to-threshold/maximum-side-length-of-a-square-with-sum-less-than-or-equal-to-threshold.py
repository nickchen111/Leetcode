class Solution:
    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:
        m, n = len(mat), len(mat[0])
        pre = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(m):
            for j in range(n):
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + mat[i][j]
        left, right = 0, min(m, n)
        def check(mid) -> bool:
            for i in range(mid, m + 1):
                for j in range(mid, n + 1):
                    if pre[i][j] - pre[i - mid][j] - pre[i][j - mid] + pre[i - mid][j - mid] <= threshold:
                        return True
            return False
        while left < right:
            mid = left + (right - left + 1) // 2
            if check(mid):
                left = mid
            else:
                right = mid - 1
        return left