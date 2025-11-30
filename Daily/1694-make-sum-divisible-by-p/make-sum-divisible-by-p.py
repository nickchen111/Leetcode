class Solution:
    def minSubarray(self, nums: List[int], p: int) -> int:
        n = len(nums)
        target = sum(nums) % p
        if target == 0:
            return 0
        mp = defaultdict(int)
        mp[0] = -1
        pre = 0
        ans = n
        for i,x in enumerate(nums):
            pre += x
            pre %= p
            # pre - target = x
            r = ((pre - target) % p + p) % p
            if r in mp:
                ans = min(ans, i - mp[r])
            mp[pre] = i
        return ans if ans != n else -1