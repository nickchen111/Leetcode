# TC:O(n) SC:O(n) 也可以轉成遞推空間壓縮成O(1)
class Solution:
    def rob(self, nums: List[int], colors: List[int]) -> int:
        '''
        就是分段做house robber
        '''
        i = 0
        ans = 0
        n = len(nums)
        def helper(start:int, end:int) -> int:
            @cache
            def dfs(i:int, choose: bool) -> int:
                if i == start - 1:
                    return 0
                if choose:
                    return dfs(i - 1, False)
                return max(dfs(i - 1, False), dfs(i - 1, True) + nums[i])
            return dfs(end, False)
                    
        while i < n:
            j = i
            while j < n and colors[i] == colors[j]:
                j += 1
            ans += helper(i, j - 1)
            i = j
        return ans
 
