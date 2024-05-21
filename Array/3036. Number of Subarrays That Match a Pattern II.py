#3036. Number of Subarrays That Match a Pattern II
# TC:O(m+n) SC:O(m+n)

class Solution:
    def countMatchingSubarrays(self, nums: List[int], s: List[int]) -> int:
       
        m = len(s)
        # 可以讓原本的list 直接多append一段list, 跟 append差別就在append只能新增一個
        # pairwise 就是直接從可迭代的資料結構取相鄰的元素
        s.extend((y>x) - (y<x) for x, y in pairwise(nums))

        n = len(s)
        z = [0]*n
        l = r = 0
        for i in range(1,n):
            if i <= r:
                z[i] = min(z[i-l], r-i+1) # 看圖取往回推的比較點z-value or 看z-box到當下pos i的當前長度是多少 取最短
            while i + z[i] < n and s[z[i]] == s[z[i]+i]:
                l,r = i, i+z[i]
                z[i] += 1
        return sum(lcp >= m for lcp in z[m:])
