# TC:O(n) SC:O(1)
class Solution:
    def minLengthAfterRemovals(self, s: str) -> int:
        return abs(sum(1 if ch == 'a' else -1  for ch in s))
