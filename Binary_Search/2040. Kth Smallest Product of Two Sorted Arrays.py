# TC:O(mlgUlgn) m 為nums1大小 n 為nums2大小 U為值域範圍 SC:O(1) 這題更狠可以做到 mlgU 但需要更複雜的分類討論...
class Solution:
    def kthSmallestProduct(self, nums1: List[int], nums2: List[int], k: int) -> int:
        '''
        明顯二分猜答案
        但要分類討論nums[i] * nums[j] <= m
        -> nums[j] <= m / nums[i]
        1. nums[i] > 0 -> nums[j] <= floor(m / nums[i]) 可以二分找
        2. nums[i] == 0 -> cnt += nums2.size() if m >= 0 else 0
        3. nums[i] < 0 -> nums[j] >= ceil(m / nums[i]) 二分找
        '''

        n, m = len(nums1), len(nums2)
        lower, upper = -10 ** 10, 10 ** 10
        def check(mid : int) -> bool:
            cnt = 0
            for i, x in enumerate(nums1):
                if nums1[i] > 0:
                    target = floor(mid / nums1[i])
                    cnt += bisect_right(nums2, target)
                elif nums1[i] == 0:
                    cnt += len(nums2) if mid >= 0 else 0
                else:
                    target = ceil(mid / nums1[i])
                    cnt += len(nums2) - 1 - bisect_left(nums2, target) + 1
            return True if cnt >= k else False
        while lower < upper:
            mid = (lower + upper) // 2
            if check(mid):
                upper = mid
            else:
                lower = mid + 1
        return lower
