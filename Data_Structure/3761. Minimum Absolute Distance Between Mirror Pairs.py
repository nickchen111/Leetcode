# TC:O(nlogU) U為最大數字的十進制長度  SC:O(n)
class Solution:
    def minMirrorPairDistance(self, nums: List[int]) -> int:
        last_index = {}
        ans = inf

        for j, x in enumerate(nums):
            if x in last_index:
                ans = min(ans, j - last_index[x])
            rev = 0
            while x > 0:
                x, d = divmod(x, 10)
                rev = rev * 10 + d
            last_index[rev] = j

        return ans if ans < inf else -1
