class Solution:
    def maxRotateFunction(self, nums: list[int]) -> int:
        n = len(nums)
        f = sum(i * x for i, x in enumerate(nums))  # F(0)
        s = sum(nums)  # nums 的总和

        ans = f
        for i in range(n - 1, 0, -1):
            f += s - n * nums[i]
            ans = max(ans, f)
        return ans