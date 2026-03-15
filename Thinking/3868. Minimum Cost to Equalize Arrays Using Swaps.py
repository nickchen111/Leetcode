# TC:O(n) SC:O(n)
class Solution:
    def minCost(self, nums1: list[int], nums2: list[int]) -> int:
        '''
        如果出現的次數不是偶數就不可能
        然後就是眾數的分法了 你多我少 貪心的分去盡量減少交換次數
        '''
        diff = Counter(nums1)
        diff.subtract(nums2) # 如果diff = Counter(nums1) - Counter(nums2) 這樣寫會讓neg變成0 是不對的
        ans = 0
        for d in diff.values():
            if d % 2:
                return -1
            if d > 0:
                ans += d >> 1
        return ans
