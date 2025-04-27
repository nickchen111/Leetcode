# TC:O(n!) SC:O(n) ans不算進去的話
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        path = [0] * n
        ans = []
        def dfs(i:int, s:Set[int]):
            if i == n:
                ans.append(path.copy())
                return
            for x in s:
                path[i] = x
                dfs(i + 1, s - {x})
        dfs(0, set(nums))
        return ans

