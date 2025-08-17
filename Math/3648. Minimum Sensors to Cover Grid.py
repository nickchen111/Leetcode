# TC:O(1) SC:O(1)
class Solution:
    def minSensors(self, n: int, m: int, k: int) -> int:
        rows = (n + 2 * k) // (2 * k + 1)
        cols = (m + 2 * k) // (2 * k + 1)
        
        return rows  * cols
