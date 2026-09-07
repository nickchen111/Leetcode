MOD = 1_000_000_007

class Solution:
    def distinctSubseqII(self, s: str) -> int:
        f = [[0] * 26 for _ in range(len(s) + 1)]
        for i, c in enumerate(s):
            c = ord(c) - ord('a')
            f[i + 1] = f[i].copy()
            f[i + 1][c] = (1 + sum(f[i])) % MOD
        return sum(f[-1]) % MOD