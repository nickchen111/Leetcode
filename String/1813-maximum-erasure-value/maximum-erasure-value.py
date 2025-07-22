max = lambda a, b:b if b > a else a
class Solution:
    def maximumUniqueSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        mp = defaultdict(int)
        i = 0
        ans = tot = 0
        for j in range(n):
            tot += nums[j]
            mp[nums[j]] += 1
            while i < n and mp[nums[j]] > 1:
                tot -= nums[i]
                mp[nums[i]] -= 1
                i += 1
            ans = max(ans, tot)
        return ans