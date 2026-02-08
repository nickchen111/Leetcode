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