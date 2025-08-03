# 二分: TC:O(nlogn) SC:O(n) 最優解: 逆向思維 雙向鍊錶 TC:O(n) SC:O(n)
class Solution:
    def minTime(self, s: str, order: List[int], k: int) -> int:
        n = len(s)
        total = n * (n + 1) // 2
        if total < k:
            return -1
        pre = list(range(-1, n))
        nxt = list(range(1, n + 2))
        for t in range(n - 1, -1, -1):
            if total < k:
                return t + 1
            i = order[t]
            l, r = pre[i], nxt[i]
            total -= (r - i) * (i - l)
            pre[r] = l
            nxt[l] = r
        return 0
        '''
        # star = [0] * n
        def check(m:int):
            # 容斥
            star_pos = order[:m+1]
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

            貢獻法
            star_set = set(order[:m+1])
            stars = [i for i in range(n) if i in star_set]
            cnt = 0
            last = -1
            for pos in stars:
                cnt += (pos - last) * (n - pos)
                last = pos
            return cnt >= k
            
            滑窗寫法
            m += 1
            for i in range(m):
                star[order[i]] = m
            cnt = 0
            last = -1
            for i, x in enumerate(star):
                if x == m:
                    last = i
                cnt += last + 1
                if cnt >= k:
                    return True
            return False
            
        lo, hi = 0, n - 1
        ans = -1
        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                hi = mid
            else:
                lo = mid + 1
        return lo
        '''
