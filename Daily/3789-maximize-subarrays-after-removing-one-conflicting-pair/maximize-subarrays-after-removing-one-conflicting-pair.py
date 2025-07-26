class Solution:
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:
        groups = [[] for _ in range(n + 1)]
        for a, b in conflictingPairs:
            if a > b:
                a, b = b, a
            groups[a].append(b)
        max_extra = extra = ans = 0
        b0 = b1 = n + 1
        for i in range(n, 0, -1):
            pre_b0 = b0
            for b in groups[i]:
                if b <= b0:
                    b0, b1 = b, b0
                elif b < b1:
                    b1 = b
            ans += b0 - i
            if pre_b0 != b0:
                extra = 0
            extra += b1 - b0
            max_extra = max(max_extra, extra)
        return ans + max_extra


