# TC: O(n) SC:O(n)
class Solution:
    def divideArray(self, nums: List[int]) -> bool:
        cnt = Counter(nums)
        target = len(nums) // 2
        for x in cnt.values():
            if x % 2:
                return False
        return True
