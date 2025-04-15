# TC:O(n * lgn) SC:O(n) SortedList 狗拍
class Solution:
    def goodTriplets(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        v_to_idx2 = [-1] * n
        for i, v in enumerate(nums2):
            v_to_idx2[v] = i # val -> idx
        ans = 0
        left = SortedList([v_to_idx2[nums1[0]]])
        right = SortedList(v_to_idx2[nums1[i]] for i in range(1, n))
        for i in range(1, n):
            x = v_to_idx2[nums1[i]]
            right.discard(x)
            left_count = left.bisect_left(x)
            right_count = (n - i - 1) - right.bisect_right(x)
            ans += left_count * right_count
            left.add(x)
        return ans
