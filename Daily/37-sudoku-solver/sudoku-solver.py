class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        BitMask優化版數獨解題器
        使用位運算大幅提升性能
        """
        n = len(board)
        rows = [0] * n
        cols = [0] * n
        grids = [0] * n
        empty_cells = []
        for i in range(n):
            for j in range(n):
                if board[i][j] == '.':
                    empty_cells.append((i, j))
                else:
                    num = int(board[i][j])
                    bit = 1 << (num - 1)
                    rows[i] |= bit
                    cols[j] |= bit
                    grids[i // 3 * 3 + j // 3] |= bit
        
        def get_candidates(i: int, j: int) -> int:
            grid_idx = i // 3 * 3 + j // 3
            used = rows[i] | cols[j] | grids[grid_idx]
            available = ((1 << 9) - 1) ^ used
            return available
        
        def backtrack(idx: int) -> bool:
            if idx == len(empty_cells):
                return True
            
            i, j = empty_cells[idx]
            grid_idx = i // 3 * 3 + j // 3
            candidates = get_candidates(i, j)
            if candidates == 0:
                return False

            while candidates:
                # 提取最低位的1
                bit = candidates & (-candidates)
                candidates ^= bit
                
                num = bit.bit_length()
                
                board[i][j] = str(num)
                rows[i] |= bit
                cols[j] |= bit
                grids[grid_idx] |= bit
                
                if backtrack(idx + 1):
                    return True
    
                board[i][j] = '.'
                rows[i] ^= bit
                cols[j] ^= bit
                grids[grid_idx] ^= bit
            
            return False
        backtrack(0)