# TC:O(n) SC:O(1)
class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        '''
        只要有相同數字 * 2 or * 3 or 三個數字是連續的就是good
        劃分型DP 我會想到每個數字當下可以代表的狀況是:
        前一個數字與我相同 or 前一個與前兩個與我相同 前兩個之間是連續的 就可以將原問題
        拆分成較小規模的子問題
        '''
        n = len(nums)
        # 空間優化
        f0, f1, f2, f3 = True, True, False, False # i-2, i-1, i, i+1
        for i in range(1,n):
            f3 = False
            if nums[i] == nums[i-1] and f1:
                f3 = True
            elif i >= 2:
                if f0 and ((nums[i] == nums[i-1] and nums[i-1] == nums[i-2]) or (nums[i] == nums[i-1] + 1 and nums[i-1] == nums[i-2] + 1)):
                    f3 = True
            
            f0, f1, f2 = f1, f2, f3
        return f3
        '''
        遞推
        f = [False] * (n+1)
        f[0] = True
        for i in range(1,n):
            if nums[i] == nums[i-1] and f[i-1]:
                f[i+1] = True
            elif i >= 2:
                if f[i-2] and ((nums[i] == nums[i-1] and nums[i-1] == nums[i-2]) or (nums[i] == nums[i-1] + 1 and nums[i-1] == nums[i-2] + 1)):
                    f[i+1] = True
        return f[n]
        '''
        '''
        @cache
        def dfs(i:int) -> bool:
            if i < 0:
                return True
            if i - 1 >= 0:
                if nums[i] == nums[i-1] and dfs(i-2):
                    return True
            if i - 2 >= 0:
                if nums[i] == nums[i-1] and nums[i-1] == nums[i-2] and dfs(i-3):
                    return True
                if nums[i] == nums[i-1] + 1 and nums[i-1] == nums[i-2] + 1 and dfs(i-3):
                    return True
            return False
        return dfs(n-1)
        '''
