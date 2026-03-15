# TC:O(n) SC:O(n)
class Solution:
    def firstUniqueEven(self, nums: list[int]) -> int:
        cnt = Counter(nums)
        for x in nums:
            if cnt[x] == 1 and x % 2 == 0:
                return x
        return -1
