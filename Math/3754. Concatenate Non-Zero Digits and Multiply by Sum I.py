# TC:O(logn) SC:O(1)
class Solution:
    def sumAndMultiply(self, n: int) -> int:
        x, s, pow10 = 0, 0, 1
        while n:
            n, d = divmod(n, 10)
            if d:
                x += d * pow10
                s += d
                pow10 *= 10
        return x * s
