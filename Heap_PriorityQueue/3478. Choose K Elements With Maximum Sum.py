# PQ + 分組循環 TC:O(nlgn) SC:O(n) 
class Solution:
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        a = sorted((x, y, i) for i, (x,y) in enumerate(zip(nums1, nums2)))
        n, i, s = len(nums1), 0, 0
        ans = [0] * n
        h = []
        while i < n:
            start = i
            x = a[start][0]
            while i < n and a[i][0] == x:
                ans[a[i][2]] = s
                i += 1 
            for j in range(start, i):
                y = a[j][1]
                s += y
                heappush(h, y)
                if len(h) > k:
                    s -= heappop(h)
        return ans
