# TC:O(n) SC:O(1)
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        and_all = reduce(operator.and_, nums)
        for x in nums:
            if x != and_all:
                return 1
        return 0
