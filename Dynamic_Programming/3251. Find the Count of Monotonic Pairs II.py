# TC:O(n*m) SC:O(m*n)
class Solution:
    def countOfPairs(self, nums: List[int]) -> int:
        '''
        可以知道arr1, arr2之間是互相影響的
        影響之餘還要滿足雙方的規則 一方越大，一方越小
        arr1 -> 小到大 x <= y
        arr2 -> 大到小 x >= y
        所以當下能填的數字會被自己前一個影響以及當前可以填的數字 以及對方的rule影響 三個變因
        nums = [2,3,2]
        arr1: 0, 0 ~ 3 等於說現在填的數字 x1 <= x2 && nums[i] - x2 <= y1 -> x2 >= nums[i] - y1, y1越小越少選擇, x1越小越多選擇
        arr2: 2, 2 ~ 3 取交集
        我現在填的數值 0 -> 之前要比0小 然後可以是現在的數字
        '''
        MOD = 10 ** 9 + 7
        n = len(nums)
        mx = max(nums)
        f = [[0] * (mx + 1) for _ in range(n)]
        for j in range(nums[0]+1):
            f[0][j] = 1
        for i in range(1,n):
            presum = list(accumulate(f[i-1]))
            for j in range(nums[i] + 1): #現在可以填什麼 nums[i-1] >= nums[i] - j
                max_k = min(j, nums[i-1] - (nums[i] - j))
                f[i][j] = presum[max_k]% MOD if max_k >= 0 else 0
        return sum(f[n-1][:nums[-1] + 1]) % MOD
        '''
        遞推
        mx = max(nums)
        f = [[0] * (mx + 1) for _ in range(n + 1)]
        for j in range(mx+1):
            f[0][j] = 1
        for i in range(n):
            for j in range(0, nums[i-1] + 1 if i - 1 >= 0 else 1): # 之前填了啥
                mx = max(j, nums[i] - (nums[i-1] - j)) if i - 1 >= 0 else j
                for k in range(mx, nums[i] + 1): # 現在可以填什麼
                    # 會發現說f[i][j]這段有可能很多數字都會用到
                    f[i + 1][k] = (f[i + 1][k] + f[i][mx]) % MOD #現在這個數字填上去後從之前可填的數字繼承過來
        return sum(f[n])
        '''

        '''
        逆著遞歸 為了遞推
        @cache
        def dfs(i: int, j: int) -> int:
            if i == 0:
                return 1
            ans = 0
            max_k = min(nums[i-1], j, nums[i-1] - (nums[i] - j))
            for k in range(max_k+1):
                ans = (ans + dfs(i - 1, k)) % MOD
            return ans

        return sum(dfs(n-1, j) for j in range(nums[-1] + 1)) % MOD
        正著遞歸
        @cache
        def dfs(i: int, prev: int) -> int:
            if i == n:
                # print("".join(t))
                return 1
            mn = prev
            ans = 0
            for j in range(mn, nums[i] + 1):
                mx = max(j, nums[i+1] - (nums[i] - j)) if i + 1 < n else j
                ans = (ans + dfs(i + 1, mx)) % MOD
            return ans

        return dfs(0, 0)
        '''
