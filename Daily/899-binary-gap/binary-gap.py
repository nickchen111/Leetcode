class Solution:
    def binaryGap(self, n: int) -> int:
        n //= (n & -n) * 2
        ans = 0
        while n > 0:
            gap = (n & -n).bit_length()
            ans = max(ans, gap)
            n >>= gap
        return ans