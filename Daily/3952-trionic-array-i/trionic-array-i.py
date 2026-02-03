class Solution:
    def isTrionic(self, nums: List[int]) -> bool:
        n = len(nums)
        i = 0

        def consume(sign: int) -> bool:
            nonlocal i
            start = i
            while i + 1 < n and (nums[i + 1] - nums[i]) * sign > 0:
                i += 1
            return i - start >= 1

        pattern = (1, -1, 1)
        i = 0
        if all(consume(s) for s in pattern) and i == n - 1:
            return True
        return False