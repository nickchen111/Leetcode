# TC:O(nlogn) SC:O(1)
class Solution:
    def perfectPairs(self, nums: List[int]) -> int:
        nums.sort(key = abs)
        ans = 0
        i = 0
        for j, v in enumerate(nums):
            while abs(v) > 2 * abs(nums[i]):
                i += 1
            ans += j - i
        return ans
