# TC:O(n) SC:O(n)
class Solution:
    def repeatedNTimes(self, nums: List[int]) -> int:
        d={}
        for i in nums:
            if i in d:
                return i
            d[i]=1
