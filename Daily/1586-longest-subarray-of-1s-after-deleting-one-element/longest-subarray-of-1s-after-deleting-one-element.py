class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        suf = [0] * n
        cnt = 0
        for i in range(n - 1, -1, -1):
            suf[i] = cnt
            if nums[i]:
                cnt += 1
            else: cnt = 0
        pre = ans = 0
        for i in range(n):
            ans = max(ans, pre + suf[i])
            if nums[i]:
                pre += 1
            else:
                pre = 0
        return ans