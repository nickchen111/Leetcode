# DP TC:O(n^2) SC:O(n)
class Solution:
    def minCost(self, nums: List[int], k: int) -> int:
        '''
        只有單獨一個的會被剔除 留下重複的, 重複的值有多少個 + k 會是這一組的value
        問說最少的value 總和是多少 代表說希望重複的值越少越好 in 每一組
        '''
        n = len(nums)
        f = [inf] * (n + 1)
        f[0] = 0
        for i in range(n):
            cnt, mp, mn = 0, [0] * n, inf
            for j in range(i, -1, -1):
                if mp[nums[j]] == 0:
                    mp[nums[j]] = 1
                    cnt += 1
                elif mp[nums[j]] == 1:
                    mp[nums[j]] = 2
                    cnt -= 1
                mn = min(mn, f[j] - j - cnt) # 只是把 f[j] + i - j + 1 - cnt + k 不變的參數拿出去
            f[i+1] = mn + k + i + 1
        return f[n]
        '''
        遞歸
        @cache
        def dfs(i:int) -> int:
            if i == n:
                return 0
            mp = [0] * n
            cnt = 0
            ans = inf
            for j in range(i, n):
                # mp[nums[j]] += 1
                if mp[nums[j]] == 0:
                    mp[nums[j]] = 1
                    cnt += 1
                elif mp[nums[j]] == 1:
                    mp[nums[j]] = 2
                    cnt -= 1
                ans = min(ans, dfs(j + 1) + j - cnt)
            return ans + k - i + 1
        return dfs(0)
        '''
