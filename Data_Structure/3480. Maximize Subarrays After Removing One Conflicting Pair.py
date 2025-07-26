# TC:O(n) SC:O(n)
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


# Sort
class Solution:
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:
        groups = [[] for _ in range(n + 1)]
        for a, b in conflictingPairs:
            if a > b:
                a, b = b, a
            groups[a].append(b)

        ans = 0
        extra = [0] * (n + 2)
        b = [n + 1, n + 1]
        for i in range(n, 0, -1):
            b = sorted(b + groups[i])[:2]  # 维護最小 b 和次小 b
            ans += b[0] - i
            extra[b[0]] += b[1] - b[0]

        return ans + max(extra)
