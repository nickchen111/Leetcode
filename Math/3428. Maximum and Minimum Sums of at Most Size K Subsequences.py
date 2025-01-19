class Solution:
    def minMaxSums(self, nums: List[int], k: int) -> int:
        nums.sort()
        ans = 0
        MOD = 10**9 + 7 
        n = len(nums)
        # for i in range(n):
        #     ans = (ans + (nums[i] * 2)) % MOD
        # 只能從 1 ~ k-1
        fac = [0] * (n+1)
        fac[0] = 1
        for i in range(1, n+1):
            fac[i] = fac[i-1] * i % MOD
        inv = [0] * (n+1)
        inv[-1] = pow(fac[-1], -1, MOD)
        for i in range(n-1, -1, -1):
            inv[i] = inv[i+1] * (i+1) % MOD
        for length in range(0, k):
            for i in range(n):
                if i >= length:
                    ans = (ans + nums[i] * fac[i] * inv[length] * inv[i - length]) % MOD
                if n - i - 1 >= length:
                    ans = (ans + nums[i] * fac[n-i-1] * inv[length] * inv[n-i-1-length]) % MOD
        return ans % MOD
