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

# 另一種思維的寫法 
class Solution:
    def calc(self, nums: List[int]) -> List[int]:
        n = len(nums)
        pre = [0] * n
        pre[0] = 1
        pre[1] = 2
        for i in range(2, n):
            if nums[i - 2] + nums[i] == nums[i - 1] * 2:
                pre[i] = pre[i - 1] + 1
            else:
                pre[i] = 2
        return pre

    def longestArithmetic(self, nums: List[int]) -> int:
        n = len(nums)
        pre = self.calc(nums)
        ans = max(pre) + 1
        if ans >= n:
            return n

        suf = self.calc(nums[::-1])[::-1]

        for i in range(1, n - 1):
            d2 = nums[i + 1] - nums[i - 1]
            if d2 % 2:
                continue

            ok_left = i > 1 and nums[i - 1] - nums[i - 2] == d2 // 2
            ok_right = i + 2 < n and nums[i + 2] - nums[i + 1] == d2 // 2

            if ok_left and ok_right:
                ans = max(ans, pre[i - 1] + 1 + suf[i + 1])
            elif ok_left:
                ans = max(ans, pre[i - 1] + 2)
            elif ok_right:
                ans = max(ans, suf[i + 1] + 2)

        return ans
