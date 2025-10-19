# TC:O(n) SC:O(n)
class Solution:
    def missingMultiple(self, nums: List[int], k: int) -> int:
        st = set(nums)
        for x in count(k, k):
            if x not in st:
                return x
