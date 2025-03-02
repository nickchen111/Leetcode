# TC:O(m + n) SC:O(1)
class Solution:
    def mergeArrays(self, nums1: List[List[int]], nums2: List[List[int]]) -> List[List[int]]:
        i, j, m, n = 0, 0, len(nums1), len(nums2)
        ans = []
        while i < m and j < n:
            if nums1[i][0] == nums2[j][0]:
                ans.append([nums1[i][0], nums1[i][1] + nums2[j][1]])
                i += 1
                j += 1
            elif nums1[i][0] > nums2[j][0]:
                ans.append([nums2[j][0], nums2[j][1]])
                j += 1
            else: 
                ans.append([nums1[i][0], nums1[i][1]])
                i += 1
        while i < m:
            ans.append([nums1[i][0], nums1[i][1]])
            i += 1
        while j < n:
            ans.append([nums2[j][0], nums2[j][1]])
            j += 1
        return ans
