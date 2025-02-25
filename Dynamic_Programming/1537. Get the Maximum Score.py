class Solution:
    def maxSum(self, nums1: List[int], nums2: List[int]) -> int:
        m, n = len(nums1), len(nums2)
        MOD = 10 ** 9 + 7
        # 空間優化
        f0, f1 = 0, 0
        i, j = 0, 0
        while i < m and j < n:
            if nums1[i] < nums2[j]:
                f0 += nums1[i]
                i += 1
            elif nums1[i] > nums2[j]:
                f1 += nums2[j]
                j += 1
            else:
                f1,f0 = max(f1,f0) + nums1[i], max(f1,f0) + nums1[i]
                i, j = i + 1, j + 1
        while i < m:
            f0 += nums1[i]
            i += 1
        while j < n:
            f1 += nums2[j]
            j += 1
        return max(f0, f1) % MO
        '''
        貪心雙指針 
        f0, f1 = [0] * (m+1), [0] * (n+1)
        i, j = 0, 0
        while i < m and j < n:
            if nums1[i] < nums2[j]:
                f0[i+1] = f0[i] + nums1[i]
                i += 1
            elif nums1[i] > nums2[j]:
                f1[j+1] = f1[j] + nums2[j]
                j += 1
            else:
                f1[j+1] = max(f1[j] + nums2[j], f0[i] + nums2[j])
                f0[i+1] = max(f0[i] + nums1[i], f1[j] + nums1[i])
                i += 1
                j += 1
        while i < m:
            f0[i+1] = f0[i] + nums1[i]
            i += 1
        while j < n:
            f1[j+1] = f1[j] + nums2[j]
            j += 1
        return max(f0[m], f1[n]) % MOD
        '''
        '''
        遞歸
        mp1 = {num: idx for idx, num in enumerate(nums1)}
        mp2 = {num: idx for idx, num in enumerate(nums2)}
        @cache
        def dfs(i:int, j:int) -> int:
            if (j == 0 and i == m) or (j == 1 and i == n):
                return 0
            ans = 0
            if j == 0:
                ans = max(dfs(mp2[nums1[i]] + 1, 1), dfs(i+1, 0)) + nums1[i] if nums1[i] in mp2 else dfs(i+1, 0) + nums1[i]
            else:
                ans = max(dfs(mp1[nums2[i]] + 1, 0), dfs(i+1, 1)) + nums2[i] if nums2[i] in mp1 else dfs(i+1, 1) + nums2[i]
            return ans
        return max(dfs(0, 0), dfs(0, 1)) % MOD
        '''
