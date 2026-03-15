# TC:O(n) SC:O(n)
class Solution:
    def gcdSum(self, nums: list[int]) -> int:
        arr = []
        mx = 0
        for x in nums:
            mx = max(mx, x)
            arr.append(gcd(mx, x))

        arr.sort()
        return sum(gcd(arr[i], arr[~i]) for i in range(len(arr) // 2))
