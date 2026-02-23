class Solution:
    def hasAllCodes(self, s: str, k: int) -> bool:
        if len(s) - k + 1 < (1 << k):
            return False
        MASK = (1 << k) - 1
        has = [False] * (1 << k)
        cnt = x = 0
        for i, ch in enumerate(s):
            x = (x << 1 & MASK) | int(ch)
            if i < k - 1 or has[x]:
                continue
            has[x] = True
            cnt += 1
            if cnt == 1 << k:
                return True
        return False
