# TC:O(n) SC:O(n)
class Solution:
    def findMaxVal(self, n: int, restrictions: List[List[int]], diff: List[int]) -> int:
        max_h = [inf] * n
        max_h[0] = 0
        
        for idx, maxVal in restrictions:
            max_h[idx] = maxVal
        for i in range(n - 1):
            if max_h[i] + diff[i] < max_h[i+1]:
                max_h[i+1] = max_h[i] + diff[i]
        for i in range(n - 2, -1, -1):
            if max_h[i+1] + diff[i] < max_h[i]:
                max_h[i] = max_h[i+1] + diff[i]
        return max(max_h)
