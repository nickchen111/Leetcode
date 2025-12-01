class Solution:
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        l, r = 0, sum(batteries) // n
        while l < r:
            x = l + (r - l + 1) // 2
            if n * x <= sum(min(b, x) for b in batteries):
                l = x
            else:
                r = x - 1
        return l