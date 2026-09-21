class Solution:
    def resultArray(self, nums: List[int], k: int) -> List[int]:
        ans = [0] * k
        f = [[0] * k for _ in range(len(nums) + 1)]
        for i, v in enumerate(nums):
            f[i + 1][v % k] = 1
            for y, c in enumerate(f[i]):
                f[i + 1][y * v % k] += c  # 刷表法
            for x, c in enumerate(f[i + 1]):
                ans[x] += c
        return ans
