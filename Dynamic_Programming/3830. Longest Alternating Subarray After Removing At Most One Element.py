# TC:O(n) SC:O(n)
class Solution:
    def longestAlternating(self, nums: List[int]) -> int:
        n = len(nums)
        pre = [[1] * 2 for _ in range(n)] # 0 下降 1上升
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                pre[i][1] = pre[i - 1][0] + 1
            elif nums[i] < nums[i - 1]:
                pre[i][0] = pre[i - 1][1] + 1
        
        suf = [[1] * 2 for _ in range(n)]
        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                suf[i][0] = suf[i + 1][1] + 1
            elif nums[i] > nums[i + 1]:
                suf[i][1] = suf[i + 1][0] + 1
        
        ans = 0
        for i in range(n):
            ans = max(ans, pre[i][0], pre[i][1])
            
        for i in range(1, n - 1):
            if nums[i - 1] < nums[i + 1]:
                ans = max(ans, pre[i - 1][0] + suf[i + 1][1])
            elif nums[i - 1] > nums[i + 1]:
                ans = max(ans, pre[i - 1][1] + suf[i + 1][0])

        return ans
