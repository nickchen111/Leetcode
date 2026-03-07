class Solution:
    def minimumOR(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        # 貪心的讓高位是0?
        mx = max(map(max, grid))
        bit_length = mx.bit_length()
        ans = 0
        for i in range(bit_length - 1, -1, -1):
            mask = ans | ((1 << i) - 1)
            for row in grid:
                for v in row:
                    if (v | mask) == mask:
                        break
                else:
                    ans |= (1 << i)
                    break
        return ans