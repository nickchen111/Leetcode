class Solution:
    def intersectionSizeTwo(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x: (x[1], x[0]))
        prev1 = prev2 = -1
        ans = 0
        for x, y in intervals:
            # print(prev1, prev2)
            if x <= prev1:
                continue
            if x <= prev2:
                prev1, prev2 = min(y - 1, prev2), y
                ans += 1
                continue
            ans += 2
            prev1, prev2 = y - 1, y
        return ans
