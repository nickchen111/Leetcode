# TC:O(n * m) SC:O(n + m)
class Solution:
    def countCoveredBuildings(self, n: int, buildings: List[List[int]]) -> int:
        row_min = defaultdict(lambda: 10**9)
        row_max = defaultdict(lambda: -10**9)
        col_min = defaultdict(lambda: 10**9)
        col_max = defaultdict(lambda: -10**9)
        
        for x, y in buildings:
            if x < row_min[y]: row_min[y] = x
            if x > row_max[y]: row_max[y] = x
            if y < col_min[x]: col_min[x] = y
            if y > col_max[x]: col_max[x] = y
        
        ans = 0
        for x, y in buildings:
            if row_min[y] < x < row_max[y] and col_min[x] < y < col_max[x]:
                ans += 1
        return ans
