class Solution:
    def minIncrementOperations(self, nums: List[int], k: int) -> int:
        '''
        每個三個一組的array裡的數字都大於等於k 問說最少需要加幾次
        每個數字會有的狀態是選擇+ or 不加 
        比k小 我加你 可以跳去前三個數字
        '''
        # 這是枚舉選哪個的思想寫出的遞推
        n = len(nums)
        f0, f1, f2 = 0, inf, inf
        for i in range(n):
            f0, f1, f2 = min(f0, f1, f2) + max(0, k - nums[i]), f0, f1
        return min(f0, f1, f2)
        '''
        枚舉選哪個的思想寫出的遞推
        f = [[inf] * (3) for _ in range(n+1)]
        f[0][0] = 0
        for i in range(n):
            f[i+1][0] = min(f[i][0], f[i][1], f[i][2]) + max(0, k - nums[i])
            f[i+1][1] = f[i][0]
            f[i+1][2] = f[i][1]
        return min(f[n][0], f[n][1], f[n][2])
        '''
        '''
        選 or 不選的遞推
        f = [[0] * (3) for _ in range(n+1)]
        for i in range(n):
            for j in range(3):
                f[i+1][j] = f[i][0] + max(0, k - nums[i])
                if j < 2:
                    f[i+1][j] = min(f[i+1][j], f[i][j+1])
        return f[n][0]
        '''
        '''
        遞歸 單狀態 枚舉選哪個思想X
        @cache
        def dfs(i:int) -> int:
            if i < 0:
                return 0
            return min(dfs(i-1), dfs(i-2), dfs(i-3)) + max(0, k - nums[i])
        return min(dfs(n-1), dfs(n-2), dfs(n-3))
        '''
        '''
        遞歸 雙狀態定義成 多用一個j表示前面有多少個數字沒處理 選 or 不選
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0:
                return 0
            if j + 1 < 3:
                return min(dfs(i-1, j + 1), dfs(i-1, 0) + max(0, k - nums[i]))
            else:
                return dfs(i-1, 0) + max(0, k - nums[i])
        return dfs(n-1, 0)
        '''
