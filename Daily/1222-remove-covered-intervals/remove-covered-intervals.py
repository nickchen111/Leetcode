class Solution:
    def removeCoveredIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x: (x[0], -x[1]))
        ans = 0
        i = 0
        n = len(intervals)
        while i < n:
            j = i + 1
            while j < n and intervals[j][1] <= intervals[i][1]:
                j += 1
            i = j
            ans += 1
        return ans
