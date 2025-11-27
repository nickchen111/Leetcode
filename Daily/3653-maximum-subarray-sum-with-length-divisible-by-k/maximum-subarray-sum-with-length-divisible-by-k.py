class Solution:
    def maxSubarraySum(self, nums: List[int], k: int) -> int:
        mp = {}
        tot = 0
        mp[0] = 0
        ans = -inf
        for i, x in enumerate(nums):
            tot += x
            length = i + 1
            m = length % k
            if m in mp:
                ans = max(ans, tot - mp[m])
                mp[m] = min(mp[m], tot)
            else:
                mp[m] = min(inf, tot)

        return ans