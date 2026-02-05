class Solution:
    def constructTransformedArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [0] * n
        for i, x in enumerate(nums):
            if x != 0:
                ans[i] = nums[((i + nums[i]) % n + n) % n]
        return ans