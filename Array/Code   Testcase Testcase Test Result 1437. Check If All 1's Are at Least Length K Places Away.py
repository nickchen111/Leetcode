# TC:O(n) SC:O(1)
class Solution:
    def kLengthApart(self, nums: List[int], k: int) -> bool:
        pos = -k - 1
        for i in range(len(nums)):
            if nums[i] == 1:
                if i - pos - 1 >= k:
                    pos = i
                else:
                    return False
        return True
