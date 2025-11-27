class Solution:
    def maxSubarraySum(self, nums: List[int], k: int) -> int:
        mp = defaultdict(int)
        tot = 0
        mp[0] = 0
        ans = -inf
        for i, x in enumerate(nums):
            tot += x
            length = i + 1
            if (length % k) in mp:
                ans = max(ans, tot - mp[length % k])
            mp[length % k] = min(mp[length % k] if length % k in mp else inf, tot)
        return ans