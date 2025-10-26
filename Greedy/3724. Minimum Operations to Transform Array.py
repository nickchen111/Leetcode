# TC:O(n) SC:O(1)
class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        cur = nums2[-1]
        diff = inf
        ans = 0
        for i in range(len(nums1)):
            diff = min(diff, abs(nums2[i] - cur), abs(nums1[i] - cur))
            mn = min(nums1[i], nums2[i])
            mx = max(nums1[i], nums2[i])
            if mn <= cur <= mx:
                diff = 0
            ans += abs(nums1[i] - nums2[i])
        
        return ans + diff + 1
