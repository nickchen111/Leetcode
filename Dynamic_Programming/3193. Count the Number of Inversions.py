# TC:O(n * lgn _ n * k) SC:O(k)
class Solution:
    def numberOfPermutations(self, n: int, requirements: List[List[int]]) -> int:
        '''
        給你一個數字代表該數組0 ~ n - 1 個數字，然後有一系列的要求說以某個idx結尾他可以產的逆序對個數要符合
        問說這個數組的排列組合狀況 有哪些是符合條件的?
        直接枚舉排列組合300! 肯定不行 n = 300 = requirement.size(), cnt <= 400
        首先會想到因為我們需要構建逆序對，把requirement 排序一下會比較好判斷 按照endpos 排序
        手玩一下: 
        逆序對i < j, nums[i] > nums[j] 所以一個數字小的 他前面有機會生成 i - 1 個逆序對 max情況下
        最多的逆序對數量是 1 + 2 + 3 + ... + n - 1 = n * (n - 1) / 2
        藉由這些推論後可以去思考說我當下這個位置選了哪個數字 他可能可以產生的逆序對數量去扣掉他在當下位置需要有的逆序對數量
        這不就可以把問題縮減成較小的子問題
        每個點如果是指定位置的話就去判斷一下當前位置
        '''
        MOD = 10 ** 9 + 7
        requirements.sort()
        req = [-1] * n
        req[0] = 0
        for end,cnt in requirements:
            req[end] = cnt
        if req[0]:
            return 0
        # 空間優化
        f = [0] * (req[-1] + 1)
        f[0] = 1 # 走到i 目前有幾對逆序對的方案數
        for i in range(1, n):
            r = req[i-1] # 之前需要的逆序對數量
            pre = list(accumulate(f, initial = 0))
            new_f = [0] * (req[-1] + 1)
            for c in range(min(req[-1], i * (i + 1) // 2) + 1): # 當下可能的逆序對數量
                if r >= 0:
                    new_f[c] = f[r] if c - i <= r and c >= r else 0
                else:
                    mn = min(i,c)
                    new_f[c] = (pre[c + 1] - pre[c - mn]) % MOD
            f = new_f.copy() # f = copy.deepcopy(new_f)
        return f[req[-1]]
        # 前綴和優化
        f = [[0] * (req[-1] + 1) for _ in range(n)]
        f[0][0] = 1 # 走到i 目前有幾對逆序對的方案數
        for i in range(1, n):
            r = req[i-1] # 之前需要的逆序對數量
            pre = list(accumulate(f[i-1], initial = 0))
            for c in range(min(req[-1], i * (i + 1) // 2) + 1): # 當下可能的逆序對數量
                if r >= 0:
                    f[i][c] = f[i-1][r] if c - i <= r and c >= r else 0
                else:
                    mn = min(i,c)
                    f[i][c] = (pre[c + 1] - pre[c - mn]) % MOD
        return f[n-1][req[-1]]
        '''
        f = [[0] * (req[-1] + 1) for _ in range(n)]
        f[0][0] = 1 # 走到i 目前有幾對逆序對的方案數
        for i in range(1, n):
            r = req[i-1] # 之前需要的逆序對數量
            for c in range(min(req[-1], i * (i + 1) // 2) + 1): # 當下可能的逆序對數量
                if r >= 0:
                    f[i][c] = f[i-1][r] if c - i <= r and c >= r else 0
                else:
                    for j in range(min(i, c) + 1):
                        f[i][c] = (f[i][c] + f[i-1][c-j]) % MOD
        return f[n-1][req[-1]]
        '''
        '''
        遞歸 TC:O(n * m * n) SC:O(n * m)
        @cache
        def dfs(i:int, c:int) -> int: # 走到i，判斷一下是否為指定位置，看他可以貢獻多少數量
            if i == 0:
                return 1
            r = req[i-1]
            if r >= 0:
                # 代表下一個有需求 我現在可以組成的對數為 c - 0,1,2....i-1 這些數字要 <= r
                return dfs(i - 1, r) % MOD if c - i <= r and c >= r else 0 
            return sum(dfs(i - 1, c - j) for j in range(min(i, c) + 1)) % MOD
        return dfs(n-1, req[-1]) % MOD
        '''
