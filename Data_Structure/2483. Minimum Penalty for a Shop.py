# TC:O(n) SC:O(1)
class Solution:
    def bestClosingTime(self, customers: str) -> int:
        suf_Y = 0
        suf_N = 0
        for c in customers:
            suf_Y += 1 if c == 'Y' else 0
            suf_N += 1 if c == 'N' else 0
        mn = suf_Y
        idx = 0
        pre_Y = pre_N = 0
        for i, c in enumerate(customers):
            pre_Y += 1 if c == 'Y' else 0
            pre_N += 1 if c == 'N' else 0
            suf_Y -= 1 if c == 'Y' else 0
            suf_N -= 1 if c == 'N' else 0
            cur = pre_N + suf_Y
            if cur < mn:
                mn = cur
                idx = i + 1
        return idx if mn <= pre_N else len(customers)
