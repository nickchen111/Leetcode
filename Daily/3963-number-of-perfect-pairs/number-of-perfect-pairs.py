class Solution:
    def perfectPairs(self, nums: List[int]) -> int:
        arr = sorted(abs(x) for x in nums)
        ans = 0
        i = 0
        for j, v in enumerate(arr):
            while v > 2 * arr[i]:
                i += 1
            ans += j - i
        return ans