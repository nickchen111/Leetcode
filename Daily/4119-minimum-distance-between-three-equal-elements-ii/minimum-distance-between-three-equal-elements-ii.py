class Solution:
    def minimumDistance(self, nums: List[int]) -> int:
        ans = inf
        mp = defaultdict(list)
        for i, x in enumerate(nums):
            mp[x].append(i)
        for k,v in mp.items():
            for i in range(2, len(v)):
                ans = min(ans, abs(v[i] - v[i-1]) + abs(v[i - 1] - v[i - 2]) + abs(v[i - 2] - v[i]))
        return ans if ans != inf else -1