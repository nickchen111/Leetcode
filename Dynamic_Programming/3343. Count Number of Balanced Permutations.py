MOD = 10 ** 9 + 7
N = 80
fac = [0] * (N+1)
fac[0] = 1
for i in range(1, N+1):
    fac[i] = fac[i-1] * i % MOD
inv = [0] * (N+1)
inv[-1] = pow(fac[-1], -1, MOD)
for i in range(N-1, -1, -1):
    inv[i] = inv[i+1] * (i+1) % MOD
class Solution:
    def countBalancedPermutations(self, num: str) -> int:
        cnt = [0] * 10
        total = 0
        n = len(num)
        for i in range(n):
            total += ord(num[i]) - ord('0')
            cnt[ord(num[i]) - ord('0')] += 1
        if total % 2:
            return 0
        target = total // 2
        @cache
        def dfs(i:int, left:int, left_sum:int) -> int:
            if i < 0:
                return 1 if left == 0 and left_sum == 0 else 0
            if left_sum < 0:
                return 0
            ans = dfs(i-1, left, left_sum)
            if left:
                ans = ans + dfs(i - 1, left - 1, left_sum - (ord(num[i]) - ord('0')))
            return ans
        ans = ((fac[n//2] * fac[n - n // 2]) % MOD * dfs(n-1, n//2, target)) % MOD
        dfs.cache_clear()
        for i in range(10):
            ans = (ans * inv[cnt[i]]) % MOD
        return ans
