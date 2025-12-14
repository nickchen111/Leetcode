class Solution:
    def numberOfWays(self, corridor: str) -> int:
        s = 0
        for c in corridor:
            if c == 'S':
                s += 1
        if s % 2 or s == 0:
            return 0
        MOD = 10 ** 9 + 7
        ans = 1
        i = 0
        n = len(corridor)
        while i < n:
            j = i
            cnt_s = 0
            # 先找出兩個S
            while j < n and cnt_s < 2:
                cnt_s += 1 if corridor[j] == 'S' else 0
                j += 1
            tmp = j - 1
            while j < n and corridor[j] != 'S':
                j += 1
            if j != n:
                ans *= j - tmp
            i = j
        return ans % MOD
