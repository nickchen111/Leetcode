class Solution:
    def reverseDegree(self, s: str) -> int:
        return sum((ord('z') - ord(x) + 1) * (i + 1) for i, x in enumerate(s))