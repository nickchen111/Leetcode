# TC:O(n) SC:O(1)
class Solution:
    def countOppositeParity(self, nums: list[int]) -> list[int]:
        n = len(nums)
        ans = [0] * n
        cnt = [0] * 2
        for i in range(n - 1, -1, -1):
            x = nums[i] % 2
            ans[i] = cnt[1 - x]
            cnt[x] += 1
        return ans
