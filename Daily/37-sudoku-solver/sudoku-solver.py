class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        n = len(board)
        rows = [[False] * (n + 1) for _ in range(n)]
        cols = [[False] * (n + 1) for _ in range(n)]
        grids = [[False] * (n + 1) for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if board[i][j] != '.':
                    rows[i][int(board[i][j])] = True
                    cols[j][int(board[i][j])] = True
                    k = i // 3 * 3 + j // 3
                    grids[k][int(board[i][j])] = True
        def backtrack(i: int, j:int) -> bool:
            if i == n:
                return True
            if j == n:
                return backtrack(i + 1, 0)
            if board[i][j] == '.':
                kk = k = i // 3 * 3 + j // 3
                for k in range(1, n + 1):
                    if not rows[i][k] and not cols[j][k] and not grids[kk][k]:
                        board[i][j] = str(k)
                        rows[i][k] = True
                        cols[j][k] = True
                        grids[kk][k] = True
                        if backtrack(i, j + 1):
                            return True
                        board[i][j] = '.'
                        rows[i][k] = False
                        cols[j][k] = False
                        grids[kk][k] = False
            else:
                return backtrack(i, j + 1)
        backtrack(0, 0)