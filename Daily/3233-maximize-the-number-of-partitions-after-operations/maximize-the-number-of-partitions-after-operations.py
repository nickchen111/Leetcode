class Solution:
    def maxPartitionsAfterOperations(self, s: str, k: int) -> int:
        if k == 26:
            return 1

        seg, mask, size = 1, 0, 0
        def update(i: int) -> None:
            nonlocal seg, mask, size
            bit = 1 << (ord(s[i]) - ord('a'))
            if mask & bit:
                return
            size += 1
            if size > k:
                seg += 1
                mask = bit
                size = 1
            else:
                mask |= bit

        n = len(s)
        suf = [None] * n + [(0, 0)]
        for i in range(n - 1, -1, -1):
            update(i)
            suf[i] = (seg, mask)

        ans = seg
        seg, mask, size = 1, 0, 0
        for i in range(n):
            suf_seg, suf_mask = suf[i + 1]
            res = seg + suf_seg
            union_size = (mask | suf_mask).bit_count()
            if union_size < k:
                res -= 1
            elif union_size < 26 and size == k and suf_mask.bit_count() == k:
                res += 1
            ans = max(ans, res)
            update(i)
        return ans
