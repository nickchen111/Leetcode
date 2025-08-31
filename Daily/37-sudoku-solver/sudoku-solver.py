class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        BitMask優化版數獨解題器
        使用位運算大幅提升性能
        """
        n = 9
        
        # 使用bitmask記錄狀態：bit i 表示數字 i+1 是否已使用
        # 例如：mask = 0b110000000 表示數字8和9已被使用
        rows = [0] * n      # rows[i] 記錄第i行已使用的數字
        cols = [0] * n      # cols[j] 記錄第j列已使用的數字
        grids = [0] * n     # grids[k] 記錄第k個3x3格已使用的數字
        
        empty_cells = []    # 記錄所有空格位置，避免重複搜索
        
        # 預處理：建立初始狀態
        for i in range(n):
            for j in range(n):
                if board[i][j] == '.':
                    empty_cells.append((i, j))
                else:
                    num = int(board[i][j])
                    bit = 1 << (num - 1)  # 數字num對應第(num-1)個bit
                    
                    rows[i] |= bit
                    cols[j] |= bit
                    grids[i // 3 * 3 + j // 3] |= bit
        
        def get_candidates(i: int, j: int) -> int:
            """
            獲取位置(i,j)的可選數字bitmask
            返回值：bit位為1表示對應數字可選
            """
            grid_idx = i // 3 * 3 + j // 3
            
            # 已使用的數字 = 行使用 | 列使用 | 格使用
            used = rows[i] | cols[j] | grids[grid_idx]
            
            # 可用數字 = 全部數字 XOR 已使用數字
            # 0b111111111 = (1 << 9) - 1 = 511，代表數字1-9都可用
            available = ((1 << 9) - 1) ^ used
            
            return available
        
        def count_bits(mask: int) -> int:
            """計算mask中有多少個1（可選數字數量）"""
            return bin(mask).count('1')
        
        def get_first_bit(mask: int) -> int:
            """獲取mask中第一個1的位置（最小可選數字）"""
            if mask == 0:
                return -1
            return (mask & -mask).bit_length() - 1
        
        def backtrack(idx: int) -> bool:
            """
            回溯算法：idx表示當前處理第幾個空格
            """
            if idx == len(empty_cells):
                return True  # 所有空格都填完了
            
            i, j = empty_cells[idx]
            grid_idx = i // 3 * 3 + j // 3
            
            # 獲取當前位置可選的數字
            candidates = get_candidates(i, j)
            
            # 如果沒有可選數字，回溯
            if candidates == 0:
                return False
            
            # 嘗試每個可選數字
            while candidates:
                # 提取最低位的1（選擇一個數字）
                bit = candidates & (-candidates)
                candidates ^= bit  # 移除這個bit
                
                num = bit.bit_length()  # bit位置+1就是數字
                
                # 放置數字
                board[i][j] = str(num)
                rows[i] |= bit
                cols[j] |= bit
                grids[grid_idx] |= bit
                
                # 遞歸下一個空格
                if backtrack(idx + 1):
                    return True
                
                # 回溯：撤銷選擇
                board[i][j] = '.'
                rows[i] ^= bit
                cols[j] ^= bit
                grids[grid_idx] ^= bit
            
            return False
        
        backtrack(0)