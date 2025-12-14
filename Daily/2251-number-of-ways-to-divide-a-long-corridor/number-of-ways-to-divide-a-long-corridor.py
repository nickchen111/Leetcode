class Solution:
    def numberOfWays(self, corridor: str) -> int:
        pos = []
        MOD = 10 ** 9 + 7
        ans = 1
        for i, c in enumerate(corridor):
            if c == 'S':
                pos.append(i)
        n = len(pos)
        if n % 2 or n == 0:
            return 0
        for i in range(2, n, 2):
            ans *= (pos[i] - pos[i - 1])
            ans %= MOD
        return ans
