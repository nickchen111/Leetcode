# TC:O(n) SC:O(n)
class Solution:
    def minimumIndex(self, nums: List[int]) -> int:
        c = Counter(nums)
        total, d = max((b, a) for a, b in c.items())

        count = 0
        for i, val in enumerate(nums):
            if val == d:
                count += 1
            if count * 2 > (i + 1) and (total - count) * 2 > len(nums) - i - 1:
                return i

        return -1
      
