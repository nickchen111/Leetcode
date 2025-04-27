# TC:O(n * n * 2^n) SC:O(15*2^n)
class Solution:
    def findPermutation(self, nums: List[int]) -> List[int]:
        n = len(nums)
        f = [[inf] * n for _ in range(1 << n)]
        record = [[-1] * n for _ in range(1 << n)]
        for j in range(n):
            f[-1][j] = abs(j - nums[0])
        for s in range((1 << n) - 1, 0, -1):
            for j in range(n):
                if s >> j & 1 == 0:
                    continue
                for k in range(n):
                    if s >> k & 1:
                        continue
                    r = f[s | (1 << k)][k] + abs(j - nums[k])
                    if r < f[s][j]:
                        f[s][j] = r
                        record[s][j] = k
        ans = []
        s = j = 0
        while j >= 0:
            ans.append(j)
            s |= (1 << j)
            j = record[s][j]
        return ans
                
        '''
        遞歸
        @cache
        def dfs(mask:int, j:int) -> int:
            if mask == (1 << n) - 1:
                return abs(j - nums[0])
            ans = inf
            for i in range(n):
                if mask >> i & 1:
                    continue
                ans = min(ans, dfs(mask | (1 << i), i) + abs(j - nums[i]))
            return ans
        dfs(1, 0) 
        ans = []
        def print_ans(mask:int, j:int) -> None:
            ans.append(j)
            if mask == (1 << n) - 1:
                return
            final_ans = dfs(mask, j)
            for i in range(n):
                if (mask >> i & 1) == 0 and dfs(mask | (1 << i), i) + abs(j - nums[i]) == final_ans:
                    print_ans(mask | ( 1 << i), i)
                    break
        print_ans(1, 0)
        return ans
        '''
            
