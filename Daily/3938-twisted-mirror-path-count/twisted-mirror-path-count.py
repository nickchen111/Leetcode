class Solution:
    def uniquePaths(self, grid: List[List[int]]) -> int:
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        dp = [[0] * n for _ in range(m)]
        dp[0][0] = 1
        
        def get_final_position(row, col, direction):
            curr_row, curr_col = row, col
            curr_dir = direction
            
            while True:
                if curr_dir == 0:  # 向右
                    curr_col += 1
                else:  # 向下
                    curr_row += 1
                
                if curr_row >= m or curr_col >= n:
                    return None
                
                if grid[curr_row][curr_col] == 0:
                    return (curr_row, curr_col)
                
                if curr_dir == 0: 
                    curr_dir = 1
                else: 
                    curr_dir = 0
        
        for i in range(m):
            for j in range(n):
                if dp[i][j] == 0:
                    continue
                
                if j + 1 < n:
                    if grid[i][j + 1] == 0:
                        dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD
                    else:
                        final_pos = get_final_position(i, j, 0)
                        if final_pos:
                            final_row, final_col = final_pos
                            dp[final_row][final_col] = (dp[final_row][final_col] + dp[i][j]) % MOD
                
                if i + 1 < m:
                    if grid[i + 1][j] == 0:
                        dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD
                    else:
                        final_pos = get_final_position(i, j, 1)
                        if final_pos:
                            final_row, final_col = final_pos
                            dp[final_row][final_col] = (dp[final_row][final_col] + dp[i][j]) % MOD
        
        return dp[m-1][n-1]