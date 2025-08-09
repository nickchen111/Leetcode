# TC:O(1)  SC:O(1)
class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        return True if n.bit_count() == 1 and n >= 1 else False
