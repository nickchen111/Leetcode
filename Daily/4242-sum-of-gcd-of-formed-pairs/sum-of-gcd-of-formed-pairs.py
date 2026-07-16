class Solution:
    def gcdSum(self, nums: List[int]) -> int:
        n = len(nums)
        pre = [0] * n
        mx = 0
        for i, x in enumerate(nums):
            mx = max(mx, x)
            pre[i] = gcd(x, mx)

        pre.sort()
        return sum(gcd(pre[i], pre[-1 - i]) for i in range(n // 2))

