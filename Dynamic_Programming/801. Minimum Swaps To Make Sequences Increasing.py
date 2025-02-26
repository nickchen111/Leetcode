# TC:O(n) SC:O(1) 
class Solution:
    def minSwap(self, nums1: List[int], nums2: List[int]) -> int:
        not_swap, swap = 0, 1
        for (a1, b1), (a2, b2) in pairwise(zip(nums1, nums2)):
            ns = s = inf
            if a1 < a2 and b1 < b2:
                ns, s = not_swap, swap + 1
            if b1 < a2 and a1 < b2:
                ns, s = min(ns, swap), min(s, not_swap + 1)
            not_swap, swap = ns, s
        return min(not_swap, swap)
        '''
        n = len(nums1)
        # 空間優化
        f0, f1 = 0, 1
        for i in range(1,n):
            prev0, prev1 = f0, f1
            f0, f1 = inf, inf
            if nums1[i] > nums1[i-1] and nums2[i] > nums2[i-1]:
                f0,f1 = prev0, prev1+1
            if nums2[i] > nums1[i-1] and nums1[i] > nums2[i-1]:
                f1, f0 = min(f1, prev0 + 1), min(f0, prev1)
        return min(f0, f1)
        '''
        '''
        遞推
        f = [[inf] * 2 for _ in range(n+1)]
        f[1][0] = 0
        f[1][1] = 1
        for i in range(1,n):
            if nums1[i] > nums1[i-1] and nums2[i] > nums2[i-1]:
                f[i+1][0] = f[i][0]
            if nums2[i] > nums1[i-1] and nums1[i] > nums2[i-1]:
                f[i+1][1] = min(f[i+1][1], f[i][0] + 1)
            if nums1[i] > nums2[i-1] and nums2[i] > nums1[i-1]:
                f[i+1][0] = min(f[i+1][0], f[i][1])
            if nums2[i] > nums2[i-1] and nums1[i] > nums1[i-1]:
                f[i+1][1] = min(f[i+1][1], f[i][1] + 1)
        return min(f[n][0], f[n][1])
        '''
        '''
        @cache
        def dfs(i:int, j:int)->int:
            if i < 0:
                return 0
            ans = inf
            if j: # 代表他之前的數字是換過的
                if nums1[i] < nums2[i+1] and nums2[i] < nums1[i+1]:
                    ans = min(ans, dfs(i-1, 0))
                if nums2[i] < nums2[i+1] and nums1[i] < nums1[i+1]:
                    ans = min(ans, dfs(i-1, 1) + 1)
            else:
                if nums1[i] < nums1[i+1] and nums2[i] < nums2[i+1]:
                    ans = min(ans, dfs(i-1, 0))
                if nums2[i] < nums1[i+1] and nums1[i] < nums2[i+1]:
                    ans = min(ans, dfs(i-1, 1) + 1)
            return ans
        return min(dfs(n-2, 0), dfs(n-2, 1) + 1)
        '''
