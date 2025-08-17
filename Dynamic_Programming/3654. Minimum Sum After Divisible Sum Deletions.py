# TC:O(n) SC:O(k)
class Solution:
    def minArraySum(self, nums: List[int], k: int) -> int:
        dp = pre = 0
        best = {0:0}
        for x in nums:
            pre = (pre + x) % k
            nxt_dp = min(dp + x, best.get(pre, inf))
            best[pre] = nxt_dp
            dp = nxt_dp
        return dp
