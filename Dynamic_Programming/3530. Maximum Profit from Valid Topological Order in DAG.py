# TC:O(n * 2 ^ n) SC:O(2 ^ n)
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        path = [0] * n
        ans = []
        on_path = 0
        def dfs(i:int):
            nonlocal on_path
            if i == n:
                ans.append(path.copy())
                return
            for j in range(n):
                if (on_path >> j) & 1:
                    continue
                path[i] = nums[j]
                on_path |= (1 << j)
                dfs(i + 1)
                on_path ^= (1 << j)
        dfs(0)
        return ans
        '''
        def dfs(i:int, s:Set[int]):
            if i == n:
                ans.append(path.copy())
                return
            for x in s:
                path[i] = x
                dfs(i + 1, s - {x})
        dfs(0, set(nums))
        return ans
        '''
