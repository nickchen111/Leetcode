# TC:O(n(lgU + n)) U為maxDiff SC:O(1)
class Solution:
    def minimizeMax(self, nums: List[int], p: int) -> int:
        nums.sort()
        n = len(nums)

        def can(mx: int) -> bool:
            count = 0
            i = 1
            while i < n:
                if nums[i] - nums[i - 1] <= mx:
                    count += 1
                    i += 2  # skip next one to avoid overlap
                else:
                    i += 1
            return count >= p

        left, right = 0, nums[-1] - nums[0]
        while left < right:
            mid = (left + right) // 2
            if can(mid):
                right = mid
            else:
                left = mid + 1
        return left

# DP
class Solution:
    def minimizeMax(self, nums: List[int], p: int) -> int:
        nums.sort()
        n = len(nums)

        def can_form(mx: int) -> bool:
            dp0, dp1 = 0, 0  # dp[i-2], dp[i-1]
            for i in range(1, n):
                if nums[i] - nums[i - 1] <= mx:
                    new_dp = max(dp1, dp0 + 1)
                    dp0, dp1 = dp1, new_dp
                else:
                    dp0, dp1 = dp1, dp1
            return dp1 >= p

        left, right = 0, nums[-1] - nums[0]
        while left < right:
            mid = (left + right) // 2
            if can_form(mid):
                right = mid
            else:
                left = mid + 1
        return left
