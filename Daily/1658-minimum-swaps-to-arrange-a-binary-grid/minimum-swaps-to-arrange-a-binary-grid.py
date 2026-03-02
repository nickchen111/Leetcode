class Solution:
    def minSwaps(self, grid: List[List[int]]) -> int:
        '''
        m = 4 那就要換到 index = 2 -> m / 2, m = 3 要換到 index = 1, 3 // 2
        先計算每個位置的000長度 然後開始判斷翻過去最少需要幾次
        '''
        n = len(grid)
        tail_zeros = [n] * n
        for i in range(n):
            for j in range(n - 1, -1, -1):
                if grid[i][j]:
                    tail_zeros[i] = n - 1 - j
                    break

        ans = 0
        for i in range(n - 1):
            need_zeros = n - 1 - i
            for j in range(i, n):
                if tail_zeros[j] >= need_zeros:
                    ans += j - i
                    tail_zeros[i + 1: j + 1] = tail_zeros[i: j]
                    break
            else:
                return -1
        return ans
