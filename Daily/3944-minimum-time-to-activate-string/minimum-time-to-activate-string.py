class Solution:
    def minTime(self, s: str, order: List[int], k: int) -> int:
        n = len(s)
        total = n * (n + 1) // 2
        if total < k:
            return -1

        def check(t):
            star_pos = order[:t+1]
            star_pos.sort()
            star_pos = [-1] + star_pos + [n]

            clean = 0
            for i in range(1, len(star_pos)):
                l = star_pos[i-1]
                r = star_pos[i]
                len_clean = r - l - 1
                if len_clean > 0:
                    clean += len_clean * (len_clean + 1) // 2
            return total - clean >= k
        lo, hi = 0, n - 1
        ans = -1
        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                hi = mid
            else:
                lo = mid + 1
        return lo