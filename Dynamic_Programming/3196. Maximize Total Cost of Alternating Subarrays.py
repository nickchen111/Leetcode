# TC:O(n) SC:O(1)
class Solution:
    def maximumTotalCost(self, nums: List[int]) -> int:
        '''
        觀察可以得出 每個數字除了開頭元素以外都有可能會有兩種狀態
        1. 當作偶數位 * -1 該項一定要前面還有人 
        2. 當作奇數位 * 1 該項抵達以後 可以無條件切割 並且賦予前一項 偶數or奇數位
        '''

        n = len(nums)
        f0, f1 = -inf, nums[0]
        for i in range(1, n):
            prev0, prev1 = f0, f1
            f0 = nums[i] * -1 + prev1
            f1 = nums[i] + max(prev0, prev1)
        return max(f0,f1)
        '''
        遞推
        f = [[-inf] * 2 for _ in range(n)]
        f[0][1] = nums[0]
        for i in range(1, n):
            f[i][0] = nums[i] * -1 + f[i-1][1]
            f[i][1] = nums[i] + max(f[i-1][0], f[i-1][1])
        return max(f[n-1][0], f[n-1][1])
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0:
                return -inf if j else 0
            if j: return nums[i] + max(dfs(i-1, 0), dfs(i-1,1))
            else: return nums[i] * -1 + dfs(i-1, 1)
        return max(dfs(n-1, 0), dfs(n-1, 1))
        '''

# 劃分型DP 思路： 每一個劃分都可以切分成兩個一組 or 一個一組 
class Solution:
    def maximumTotalCost(self, nums: List[int]) -> int:
        n = len(nums)
        # 空間優化
        f0, f1 = 0, nums[0]
        for i in range(1,n):
            prev0, prev1 = f0, f1
            f0 = f1
            f1 = max(prev1 + nums[i], prev0 + nums[i-1] - nums[i])
        return f1
        '''
        遞推 
        f = [-inf] * (n+1)
        f[0] = 0
        f[1] = nums[0]
        for i in range(1,n):
            f[i+1] = max(f[i] + nums[i], f[i-1] + nums[i-1] - nums[i])
        return f[n]
        '''
        '''
        遞歸 TC:O(n) SC:O(n)
        @cache
        def dfs(i:int) ->int:
            if i == 0:
                return nums[0]
            if i < 0:
                return 0
            return max(dfs(i-1) + nums[i], dfs(i-2) + nums[i-1] - nums[i])
        return dfs(n-1)
        '''
