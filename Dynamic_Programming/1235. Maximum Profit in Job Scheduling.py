# TC:O(nlgn) SC:O(n)
class Solution:
    def jobScheduling(self, startTime: List[int], endTime: List[int], profit: List[int]) -> int:
        '''
        題目中的timestamp 很大 需要離散化，但是區間個數是可以下手的方向
        '''
        n = len(startTime)
        interval = sorted(zip(endTime, startTime, profit))
        dp = [0] * (n+1)
        for i in range(n):
            end, start, gain = interval[i]
            j = bisect_right(interval, (start, inf, inf), 0, i)
            dp[i+1] = max(dp[i], dp[j] + gain)
        return dp[-1]

        
