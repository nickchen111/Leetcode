# TC:O(n^2) SC:O(n^2)
class Solution:
    def lenLongestFibSubseq(self, nums: List[int]) -> int:
        '''
        只要第三個數字是由前兩個數字組合而成就可以算是本題的費氏數列的數字
        f[i][j] 以i, j 兩個數字作結尾可以組成的最長長度
        '''
        n = len(nums)
        f = [[2] * n for _ in range(n)]
        ans = 0
        mp = defaultdict(int)
        for i in range(n):
            mp[nums[i]] = i
            for j in range(i+1, n):
                diff = nums[j] - nums[i]
                if diff in mp and mp[diff] < i:
                    index = mp[diff]
                    if f[index][i] + 1 > f[i][j]:
                        f[i][j] = f[index][i] + 1
                        if f[i][j] > ans:
                            ans = f[i][j]
        return ans if ans >= 3 else 0
        '''
        遞歸
        mp = {nums[i]: i for i in range(n)}

        @cache
        def dfs(i: int, j: int) -> int:
            diff = nums[j] - nums[i]
            # 如果 diff 不存在或其索引不在 i 之前，就表示不能延續
            if diff not in mp or mp[diff] >= i:
                return 2
            return dfs(mp[diff], i) + 1
        ans = 0
        for i in range(n):
            for j in range(i+1, n):
                ans = max(ans, dfs(i, j))
        dfs.cache_clear()
        return ans if ans >= 3 else 0
        '''

