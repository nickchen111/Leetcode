class Solution:
    def maxSum(self, nums: List[int]) -> int:
        n = len(nums)
        cnt = defaultdict(int)
        mx = -101
        ans = 0
        for x in nums:
            if x > 0 and cnt[x] == 0:
                ans += x
                cnt[x] += 1
            mx = max(mx, x)
        return ans if mx >= 0 else mx