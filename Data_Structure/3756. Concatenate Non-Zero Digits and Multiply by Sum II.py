# TC:O(n) SC:O(n)
MOD = 1_000_000_007
MAX_N = 100_001

pow10 = [1] * MAX_N
for i in range(1, MAX_N):
    pow10[i] = (pow10[i - 1] * 10) % MOD

class Solution:
    def sumAndMultiply(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        sum_d = [0] * (n + 1)
        pre_num = [0] * (n + 1)
        sum_non_zero = [0] * (n + 1)
        for i, d in enumerate(map(int, s)):
            sum_d[i + 1] = sum_d[i] + d
            pre_num[i + 1] = (pre_num[i] * 10 + d) % MOD if d else pre_num[i]
            sum_non_zero[i + 1] = sum_non_zero[i] + (d > 0)

        ans = []
        for l, r in queries:
            r += 1
            length = sum_non_zero[r] - sum_non_zero[l]
            x = pre_num[r] - pre_num[l] * pow10[length]
            ans.append(x * (sum_d[r] - sum_d[l]) % MOD)
        return ans
