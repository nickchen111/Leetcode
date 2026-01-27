# TC:O(n) SC:O(n) 兩種寫法
class Solution:
    def rotateElements(self, nums: List[int], k: int) -> List[int]:
        a = [x for x in nums if x >= 0]
        if not a:
            return nums
        k %= len(a)
        a = a[k:] + a[:k]
        j = 0
        for i, x in enumerate(nums):
            if x >= 0:
                nums[i] = a[j]
                j += 1
        return nums

# 
class Solution:
    def rotateElements(self, nums: List[int], k: int) -> List[int]:
        a = [x for x in nums if x >= 0]
        m = len(a)
        j = k
        for i, x in enumerate(nums):
            if x >= 0:
                nums[i] = a[j % m]
                j += 1
        return nums
