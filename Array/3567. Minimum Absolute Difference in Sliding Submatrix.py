# TC:O( (m - k) * (n - k) * k * k * lgk) SC:O(k* k)
class Solution:
    def minAbsDiff(self, grid: List[List[int]], k: int) -> List[List[int]]:
        '''
        問說每個submatrix 最小絕對值差是多少，並且如果數字都一樣那就是0 
        '''
        m, n = len(grid), len(grid[0])
        ans = [[0] * (n - k + 1) for _ in range(m - k + 1)]
        for i in range(m - k + 1):
            sub_grid = grid[i: i + k]
            for j in range(n - k + 1):
                # 把每一個數字記錄起來
                tmp = []
                for row in sub_grid:
                    tmp.extend(row[j:j+k])
                tmp.sort()
                ret = inf
                for x, y in pairwise(tmp):
                    if x < y:
                        ret = min(ret, y - x)
                if ret != inf:
                    ans[i][j] = ret
        return ans
