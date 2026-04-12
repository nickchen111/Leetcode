# 前後綴分解 TC:O(n) SC:O(1)
class Solution:
    def minIncrease(self, nums: List[int]) -> int:
        n = len(nums)
        suf = 0
        for i in range(n - 2, 0, -2):
            suf += max(max(nums[i - 1], nums[i + 1]) - nums[i] + 1, 0)

        if n % 2 > 0:
            return suf

        ans = suf
        pre = 0
        for i in range(1, n - 1, 2):
            pre += max(max(nums[i - 1], nums[i + 1]) - nums[i] + 1, 0)
            suf -= max(max(nums[i], nums[i + 2]) - nums[i + 1] + 1, 0)
            ans = min(ans, pre + suf)

        return ans

# 狀態機DP TC:O(n) SC:O(n)
class Solution:
    def minIncrease(self, nums: list[int]) -> int:
        n = len(nums)
        dp = [(0, 0)] * n
        
        for i in range(1, n - 1):
            res_no = dp[i-1]
            cur_cost = max(0, nums[i-1] - nums[i] + 1, nums[i+1] - nums[i] + 1)
            prev_cnt, prev_cost = dp[i-2] if i >= 2 else (0, 0)
            res_yes = (prev_cnt - 1, prev_cost + cur_cost)
            dp[i] = min(res_no, res_yes)
            
        return dp[n-2][1]
