# TC:O(n) SC:O(1)
class Solution:
    def minimumIndex(self, capacity: list[int], itemSize: int) -> int:
        ans = n = len(capacity)
        min_c = inf
        for i, c in enumerate(capacity):
            if c >= itemSize and c < min_c:
                ans = i
                min_c = c
        return ans if ans != n else -1
                
