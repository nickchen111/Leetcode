# Math: TC:O(nlglgU) SC:O(n)
class Solution:
    def longestSquareStreak(self, nums: List[int]) -> int:
        s = set(nums)
        ans = -1
        for x in s:
            cnt = 0
            while x in s:
                cnt += 1
                x *= x
            if cnt >= 2 and cnt > ans:
                ans = cnt

        return ans

# DP TC:O(n) SC:O(n)
class Solution:
    def longestSquareStreak(self, nums: List[int]) -> int:
        s = set(nums)
        @cache
        def dfs(x:int) ->int:
            if x not in s:
                return 0
            return 1 + dfs(x * x)
        ans = max(map(dfs, s))
        return ans if ans > 1 else -1
