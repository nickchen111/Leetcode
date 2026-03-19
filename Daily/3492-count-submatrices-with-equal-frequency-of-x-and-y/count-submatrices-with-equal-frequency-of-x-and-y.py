class Solution:
    def numberOfSubmatrices(self, grid: List[List[str]]) -> int:
        col_sum = [0] * len(grid[0])
        ans = 0
        col_check = [False] * len(grid[0])
        for row in grid:
            s = 0
            flag = False
            for j, x in enumerate(row):
                if x == 'X':
                    flag = True
                    col_sum[j] += 1
                elif x == 'Y':
                    col_sum[j] -= 1
                flag = flag or col_check[j]
                col_check[j] = (col_check[j - 1] if j - 1 >= 0 else False) or flag 
                s += col_sum[j]
                if s == 0 and col_check[j]:
                    ans += 1
        return ans
