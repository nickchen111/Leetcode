class Solution:
    def findClosest(self, x: int, y: int, z: int) -> int:
        diff1, diff2 = abs(x - z), abs(y - z)
        if diff1 < diff2:
            return 1
        elif diff2 < diff1:
            return 2
        return 0
