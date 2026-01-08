class Solution:
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        n, m = len(nums1), len(nums2)
        dp = [[-inf] * (m + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        for i in range(n):
            for j in range(m):
                dp[i+1][j+1] = max(dp[i + 1][j + 1], dp[i][j] + nums1[i] * nums2[j], nums1[i] * nums2[j], dp[i + 1][j], dp[i][j + 1])
        return dp[n][m]