# TC:O(n) SC:O(1)
class Solution:
    def smallestBalancedIndex(self, nums: List[int]) -> int:
        pre = sum(nums)
        mul = 1
        for i in range(len(nums) - 1, 0, -1):
            pre -= nums[i]
            if pre < mul:
                return -1
            if pre == mul:
                return i
            # if mul > pre // nums[i]: 這個就是將乘法轉成除法防止溢出 下取整
            #     break
            mul *= nums[i]
        return -1
