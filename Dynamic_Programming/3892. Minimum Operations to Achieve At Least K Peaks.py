# TC:O(n) SC:O(n)
class Solution:
    def solve(self, a: List[int], k: int) -> int:
        @cache
        def dfs(left: int, i: int) -> int:
            if left == 0:
                return 0
            if left > (i + 1) // 2:  # i=-1 時 (i+1)//2 = 0，left>=1 必然 > 0 → return inf
                return inf

            # 選or不選
            not_choose = dfs(left, i - 1)
            choose = dfs(left - 1, i - 2) + max(max(a[i - 1], a[i + 1]) - a[i] + 1, 0)
            return min(not_choose, choose)

        return dfs(k, len(a) - 2)

    def minOperations(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if k > n // 2:
            return -1

        cnt = 0
        for i in range(n):
            if nums[i - 1] < nums[i] > nums[(i + 1) % n]:
                cnt += 1
        if cnt >= k: # 如果已經有k個峰值
            return 0

        # 如果 nums[0] 是峰值，那麼 nums[-1] 不是峰值
        ans1 = self.solve([nums[-1]] + nums, k)
        # 如果 nums[0] 不是峰值
        ans2 = self.solve(nums + [nums[0]], k)
        return min(ans1, ans2)
