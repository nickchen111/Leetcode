# TC:O(n) SC:O(n)
class Solution:
    def minOperations(self, nums: List[int], target: List[int]) -> int:
        return len({x for x, y in zip(nums, target) if x != y})
