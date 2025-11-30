class Solution:
    def minMirrorPairDistance(self, nums: List[int]) -> int:
        n = len(nums)
        ans = inf
        mp = defaultdict(list)
        for i in range(n):
            mp[nums[i]].append(i)
        for i, x in enumerate(nums):
            tmp = 0
            while x:
                x, d = divmod(x, 10)
                tmp = tmp * 10 + d
            if tmp in mp:
                r = bisect_right(mp[tmp], i)
                if r < len(mp[tmp]):
                    ans = min(ans, mp[tmp][r] - i)
        return ans if ans != inf else -1