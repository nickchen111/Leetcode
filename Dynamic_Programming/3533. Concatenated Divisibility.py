# TC:O(n * k * 2 ^ n + nlgn) SC:O(n * k + n)
class Solution:
    def concatenatedDivisibility(self, nums: List[int], k: int) -> List[int]:
        nums.sort()
        length = [10 ** len(str(x)) for x in nums]
        n = len(nums)
        ans = []
        @cache
        def dfs(mask:int, mod:int):
            if mask == 0:
                return mod == 0
            for j in range(n):
                if mask & (1 << j) and dfs(mask ^ (1 << j), (mod * length[j] + nums[j]) % k):
                    ans.append(nums[j])
                    return True
            return False
        if not dfs((1 << len(nums)) - 1, 0):
            return []
        ans.reverse()
        return ans
