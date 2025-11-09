# TC:O(n) SC:O(n)
class Solution:
    def minimumDistance(self, nums: List[int]) -> int:
        mp = defaultdict(list)
        for i, x in enumerate(nums):
            mp[x].append(i)
        ans = inf
        for k, v in mp.items():
            if len(v) < 3:
                continue
            for i in range(2, len(v)):
                ans = min(ans, v[i] - v[i - 1] + v[i] - v[i - 2] + v[i - 1] - v[i - 2])
        return ans if ans != inf else -1
