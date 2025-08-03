# TC:O(n) SC:O(1)
class Solution:
    def earliestFinishTime(self, landStartTime: List[int], landDuration: List[int], waterStartTime: List[int], waterDuration: List[int]) -> int:
        mn_st = min(ls + ld for ls, ld in zip(landStartTime, landDuration))
        ans = inf
        for ws, wd in zip(waterStartTime, waterDuration):
            if ws <= mn_st:
                ans = min(ans, mn_st + wd)
            else:
                ans = min(ans, ws + wd)
        mn_st = min(ws + wd for ws, wd in zip(waterStartTime, waterDuration))
        for ls, ld in zip(landStartTime, landDuration):
            if ls <= mn_st:
                ans = min(ans, mn_st + ld)
            else:
                ans = min(ans, ls + ld)
        return ans
        
        
        
