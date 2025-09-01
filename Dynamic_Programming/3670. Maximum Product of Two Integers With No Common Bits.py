# 第一種寫法 
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        B = max(nums).bit_length()
        u = 1 << B

        f = [0] * u
        for x in nums:
            f[x] = x

        for b in range(B):
            bit = 1 << b
            for mask in range(u):
                if mask & bit:
                    if f[mask ^ bit] > f[mask]:
                        f[mask] = f[mask ^ bit]

        return max(x * f[(u - 1) ^ x] for x in nums)

# 優化 TC:O(n + UlogU) U = 20 SC:O(U)
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        B = max(nums).bit_length()
        u = 1 << B

        f = [0] * u
        for x in nums:
            f[x] = x

        for b in range(B):
            bit = 1 << b
            s = 3
            while s < u:
                s |= bit
                v = f[s ^ bit]
                if v > f[s]:
                    f[s] = v
                s += 1

        return max(x * f[(u - 1) ^ x] for x in nums)
