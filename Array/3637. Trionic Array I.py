# TC:O(n) SC:O(1)
class Solution:
    def isTrionic(self, nums: List[int]) -> bool:
        n = len(nums)
        p = 1
        while p < n and nums[p] > nums[p - 1]:
            p += 1
        if p == n or p == 1:
            return False
        q = p
        while q < n and nums[q] < nums[q - 1]:
            q += 1
        
        if q == p:
            return False
        if q == n:
            return False
        # print(q)
        for i in range(q, n):
            if nums[i] <= nums[i - 1]:
                return False
        
        return True
