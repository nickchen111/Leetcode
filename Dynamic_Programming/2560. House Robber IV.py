# TC:O(nlgn) SC: O(n) ->優化 O(1) DP vs Greedy
class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        def solve(mx: int) -> int:
            f0 = f1 = 0
            for x in nums:
                if x > mx:
                    f0 = f1
                else:
                    f0, f1 = f1, max(f1, f0 + 1)
            return f1
        return bisect_left(range(max(nums)+1), k, key=solve)

class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        def solve(mx: int) -> int:
            cnt = i = 0
            while i < len(nums):
                if nums[i] > mx:  # 不偷
                    i += 1
                else:  # 立刻偷
                    cnt += 1
                    i += 2  # 跳過下一間房子
            return cnt
        return bisect_left(range(max(nums)), k, key=solve)
