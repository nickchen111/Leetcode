class Solution:
    def check(self, nums: List[int]) -> bool:
        is_sorted = True
        for x, y in pairwise(nums):
            if x > y:
                if not is_sorted:
                    return False
                is_sorted = False 
        return is_sorted or nums[0] >= nums[-1]
