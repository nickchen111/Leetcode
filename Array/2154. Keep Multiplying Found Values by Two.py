# TC:O(n) SC:O(n)
class Solution:
    def findFinalValue(self, nums: List[int], original: int) -> int:
        st = set(nums)
        while original in st:
            original <<= 1
        return original
        
