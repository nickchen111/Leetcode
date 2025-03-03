# TC:O(n) SC:O(1)
class Solution:
    def pivotArray(self, nums: List[int], pivot: int) -> List[int]:
        less, same = 0, 0
        for x in nums:
            less += 1 if x < pivot else 0
            same += 1 if x == pivot else 0
        first, second = 0, less + same
        ans = [0] * len(nums)
        for x in nums:
            if x < pivot:
                ans[first] = x
                first += 1
            elif x == pivot:
                ans[less] = x
                less += 1
            else:
                ans[second] = x
                second += 1
        return ans
