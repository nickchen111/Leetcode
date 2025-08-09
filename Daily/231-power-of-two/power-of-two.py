class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        print(n.bit_count())
        return True if n.bit_count() == 1 and n >= 1 else False