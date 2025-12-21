# TC:O(logn) SC:O(1)
class Solution:
    def mirrorDistance(self, n: int) -> int:
        s = list(str(n))
        return abs(n - int(''.join(s[::-1])))
