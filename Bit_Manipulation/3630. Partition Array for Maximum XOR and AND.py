# TC:O(n * 2^n * logU) SC:O(2 ^ n + logU)
class XorBasis:
    def __init__(self, n: int):
        self.b = [0] * n

    def insert(self, x: int) -> None:
        b = self.b
        while x:
            i = x.bit_length() - 1
            if b[i] == 0:
                b[i] = x
                return
            x ^= b[i] 
    
    def max_xor(self) -> int:
        b = self.b
        res = 0

        for i in range(len(b) - 1, -1, -1):
            if res ^ b[i] > res:
                res ^= b[i]
        return res


class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        n = len(nums)
        sz = max(nums).bit_length()

        # 預處理所有子集的 AND 和 XOR
        u = 1 << n
        sub_and = [0] * u
        sub_xor = [0] * u
        sub_and[0] = -1
        for i, x in enumerate(nums):
            high_bit = 1 << i
            for mask in range(high_bit):
                sub_and[high_bit | mask] = sub_and[mask] & x
                sub_xor[high_bit | mask] = sub_xor[mask] ^ x
        sub_and[0] = 0

        def max_xor2(sub: int) -> int:
            b = XorBasis(sz)
            xor = sub_xor[sub]
            for i, x in enumerate(nums):
                if sub >> i & 1:
                    # 只考虑有偶数個 1 的比特位（xor 在這些比特位上是 0）
                    b.insert(x & ~xor)
            return xor + b.max_xor() * 2

        return max(sub_and[i] + max_xor2((u - 1) ^ i) for i in range(u))
