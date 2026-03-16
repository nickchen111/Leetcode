# TC:O(n) SC:O(n)
class Solution:
    def longestArithmetic(self, nums: List[int]) -> int:
        n = len(nums)
        suf = [(inf, 0) for _ in range(n)]
        suf[-1] = (inf, 1) # diff, length
        ans = 1
        for i in range(n - 2, -1, -1):
            d = nums[i + 1] - nums[i]
            pd, pl = suf[i + 1]
            l = pl + 1 if pd in (inf, d) else 2
            suf[i] = (d, l)
            ans = max(ans, l)
            
        pre = [(inf, 0) for _ in range(n)]
        pre[0] = (inf, 1)
        ans = max(ans, 1 + suf[1][1])
        for i in range(1, n):
            d = nums[i] - nums[i - 1]
            pd, pl = pre[i - 1]
            pre[i] = (d, pl + 1 if pd in (inf, d) else 2)

        ans = max(ans, pre[-2][1] + 1)
        for i in range(1, n - 1):
            ans = max(ans, pre[i - 1][1] + 1, suf[i + 1][1] + 1)
            gap = nums[i + 1] - nums[i - 1]
            if gap % 2 == 0:
                d = gap // 2
                L = pre[i - 1][1] if pre[i - 1][0] == d else 1
                R = suf[i + 1][1] if suf[i + 1][0] == d else 1
                ans = max(ans, L + 1 + R)
        return ans
