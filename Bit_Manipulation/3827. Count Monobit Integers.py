# TC:O(1) SC:O(1)
class Solution:
    def countMonobit(self, n: int) -> int:
        b = n.bit_length()
        return b + 1 if n == (1 << b) - 1 else b
