class Solution:
    def maximumJumps(self, nums: List[int], target: int) -> int:
        @cache
        def dfs(j:int) -> int:
            if j == 0:
                return 0
            ret = -inf
            for i in range(j):
                if abs(nums[i] - nums[j]) <= target:
                    ret = max(ret, dfs(i) + 1)
            return ret
        ans = dfs(len(nums) - 1)
        return -1 if ans < 0 else ans
