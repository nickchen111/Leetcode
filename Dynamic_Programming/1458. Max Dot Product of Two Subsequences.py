# TC:O(n^2) SC:O(n^2) -> O(n)
class Solution:
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        # 選 or 不選
        m,n = len(nums1), len(nums2)
        dp = [float('-inf')] * (n+1)
        dp[0] = 0
        for i, x in enumerate(nums1):
            prev = dp[0]
            dp[0] = float('-inf')
            for j, y in enumerate(nums2):
                tmp = dp[j+1]
                dp[j+1] = max(prev + nums1[i] * nums2[j], nums1[i] * nums2[j], dp[j], dp[j+1])
                prev = tmp
        return dp[n]
        """
        遞推 二維
        dp = [[float('-inf')] * (n+1) for _ in range(m+1)]
        dp[0][0] = 0
        for i, x in enumerate(nums1):
            for j, y in enumerate(nums2):
                dp[i+1][j+1] = max(dp[i][j] + nums1[i] * nums2[j], nums1[i] * nums2[j], dp[i+1][j], dp[i][j+1])
        return dp[m][n]
        """
        """
        遞歸 
        @cache
        def dfs(i, j) -> int:
            if i < 0 or j < 0:
                return  float('-inf')
            return max(dfs(i-1, j-1) + nums1[i] * nums2[j], dfs(i-1,j), dfs(i,j-1),nums1[i] * nums2[j])
        return dfs(m-1, n-1)
        """
