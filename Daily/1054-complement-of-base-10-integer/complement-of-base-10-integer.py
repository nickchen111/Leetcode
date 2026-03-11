class Solution:
    def bitwiseComplement(self, n: int) -> int:
        # 取反
        if n == 0:
            return 1
        w = n.bit_length()
        return ((1 << w) - 1) ^ n