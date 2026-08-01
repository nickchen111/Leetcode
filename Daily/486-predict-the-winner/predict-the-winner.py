class Solution:
    def predictTheWinner(self, nums: List[int]) -> bool:

        @cache
        def dfs(l:int, r:int) -> int:
            if l == r:
                return nums[l]
            if l > r:
                return 0
            ret = max(nums[l] + min(dfs(l + 2, r), dfs(l + 1, r - 1)), nums[r] + min(dfs(l + 1, r - 1), dfs(l, r - 2)))
            return ret
        tot = dfs(0, len(nums) - 1)
        return tot >= sum(nums) - tot