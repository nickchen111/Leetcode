class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        d = abs(hour * 30 - minutes * 5.5)
        return min(d, 360 - d)