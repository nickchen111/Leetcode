# 把矩阵 a 顺时针旋转 90°
def rotate(a: List[List[int]]) -> List[List[int]]:
    return list(zip(*reversed(a)))

class Solution:
    def minimumSum(self, grid: List[List[int]]) -> int:
        return min(self.solve(grid), self.solve(rotate(grid)))

    def solve(self, a: List[List[int]]) -> int:
        # 3195. 包含所有 1 的最小矩形面积 I
        # 限定在 a 的 [l,r) 列中
        def minimumArea(a: List[List[int]], l: int, r: int) -> int:
            left = top = inf
            right = bottom = 0
            for i, row in enumerate(a):
                for j, x in enumerate(row[l:r]):
                    if x:
                        left = min(left, j)
                        right = max(right, j)
                        top = min(top, i)
                        bottom = i
            return (right - left + 1) * (bottom - top + 1)

        ans = inf
        m, n = len(a), len(a[0])

        if m >= 3:
            for i in range(1, m):
                for j in range(i + 1, m):
                    area = minimumArea(a[:i], 0, n)
                    area += minimumArea(a[i:j], 0, n)
                    area += minimumArea(a[j:], 0, n)
                    ans = min(ans, area)

        if m >= 2 and n >= 2:
            for i in range(1, m):
                for j in range(1, n):
                    area = minimumArea(a[:i], 0, n)
                    area += minimumArea(a[i:], 0, j)
                    area += minimumArea(a[i:], j, n)
                    ans = min(ans, area)

                    area = minimumArea(a[:i], 0, j)
                    area += minimumArea(a[:i], j, n)
                    area += minimumArea(a[i:], 0, n)
                    ans = min(ans, area)
        return ans