class Solution:
    def maxTwoEvents(self, events):
        events.sort(key=lambda x: x[1])

        dp = SortedDict()
        dp[0] = 0

        res = 0
        maxVal = 0

        for s, e, v in events:
            idx = dp.bisect_left(s) - 1
            best_before = dp.peekitem(idx)[1]
            res = max(res, best_before + v)
            maxVal = max(maxVal, v)
            dp[e] = maxVal

        return res
