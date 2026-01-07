# TC:O(nm) SC:O(m)
class Solution:
    def numberOfRoutes(self, grid: List[str], d: int) -> int:
        n, m = len(grid), len(grid[0])
        MOD = 10**9 + 7
        start_at_bottom = [1 if char == '.' else 0 for char in grid[n-1]]
        if sum(start_at_bottom) == 0:
            return 0
        
        v_limit = int(isqrt(max(0, d*d - 1)))
        h_limit = d
        
        def get_range_sum(pref, left, right):
            l = max(0, left)
            r = min(m - 1, right)
            return (pref[r+1] - pref[l]) % MOD

        pref_init = list(accumulate(start_at_bottom, initial = 0))
        dp0 = list(start_at_bottom) # 下面來的
        dp1 = [0] * m # 水平跳
        for c in range(m):
            if grid[n-1][c] == '.':
                total = get_range_sum(pref_init, c - h_limit, c + h_limit)
                dp1[c] = (total - start_at_bottom[c] + MOD) % MOD

        for r in range(n - 1, 0, -1):
            pref_both = list(accumulate((a + b for a, b in zip(dp0, dp1)), 
                        lambda x, y: (x + y) % MOD, 
                        initial=0))
            next_dp0 = [0] * m
            for c in range(m):
                if grid[r-1][c] == '.':
                    next_dp0[c] = get_range_sum(pref_both, c - v_limit, c + v_limit)
            dp0 = next_dp0

            pref_next0 = list(accumulate(dp0, initial=0))
            next_dp1 = [0] * m
            for c in range(m):
                if grid[r-1][c] == '.':
                    total = get_range_sum(pref_next0, c - h_limit, c + h_limit)
                    next_dp1[c] = (total - dp0[c] + MOD) % MOD
            dp1 = next_dp1
        return (sum(dp0) + sum(dp1)) % MOD
