class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        n = len(board)

        row = [[0] * (n + 1) for _ in range(n + 1)]
        col = [[0] * (n + 1) for _ in range(n + 1)]
        grid = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n):
            for j in range(n):
                if board[i][j] != '.':
                    k = (i // 3) * 3 + (j // 3)
                    num = int(board[i][j])
                    print(num)
                    if row[i][num] or col[j][num] or grid[k][num]:
                        return False
                    row[i][num] = col[j][num] = grid[k][num] = 1
        return True
