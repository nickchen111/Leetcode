# TC:O(n * 2 ^ n) SC:O(1)
class Solution:
    def checkEqualPartitions(self, nums: List[int], target: int) -> bool:
        '''
        背包!? 每一個元素乘上去會等於target
        n * 2 ^ n
        '''
        # 二進制枚舉
        u = 1 << len(nums) - 1
        for mask in range(1, u):
            mul1, mul2 = 1, 1
            for i in range(len(nums)):
                if (mask >> i) & 1:
                    mul1 *= nums[i]
                else:
                    mul2 *= nums[i]
            if mul1 == target and mul2 == target:
                return True
        return False

        '''
        背包寫法
        tot = 1
        n = len(nums)
        for x in nums:
            tot *= x
        if tot // target != target:
            return False
        @cache
        def dfs(i:int, cur_sum:int, flag:bool):
            if cur_sum == target and flag:
                return True
            if i == n:
                return False
            if cur_sum > target:
                return False
            return dfs(i + 1, cur_sum * nums[i], True) or dfs(i + 1, cur_sum, flag)
        return dfs(0, 1, False)
        '''
