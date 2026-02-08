# TC:O(n * m * k) SC:O(n * m * k)
class Solution:
    def maxScore(self, nums1: List[int], nums2: List[int], K: int) -> int:
        '''
        n = m = k = 100
        '''
        @cache
        def dfs(i:int, j:int, k:int) -> int:
            if k == 0:
                return 0 
            if i + 1 < k or j + 1 < k:
                return -inf
            # 選 or 不選
            return max(dfs(i - 1, j - 1, k - 1) + nums1[i] * nums2[j], dfs(i - 1, j, k), dfs(i, j - 1, k))
        ans = dfs(len(nums1) - 1, len(nums2) - 1, K)
        dfs.cache_clear()
        return ans

# 遞推
class Solution:
    def maxScore(self, nums1: List[int], nums2: List[int], K: int) -> int:
        n, m = len(nums1), len(nums2)
        f = [[[-inf] * (m + 1) for _ in range(n + 1)] for _ in range(K + 1)]
        f[0] = [[0] * (m + 1) for _ in range(n + 1)]
        for k in range(1, K + 1):
            for i in range(k - 1, n):
                for j in range(k - 1, m):
                    f[k][i + 1][j + 1] = max(f[k][i][j + 1], f[k][i + 1][j], f[k - 1][i][j] + nums1[i] * nums2[j])
        return f[K][n][m]
