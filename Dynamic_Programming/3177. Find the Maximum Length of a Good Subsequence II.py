# TC:O(n * k) SC:O(k)
class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        '''
        最多只能有k個不同pair, 其他要相同的最長子序列
        走到i的時候最多j個不同pair 可以有的最長長度？
        dfs(i, j, prev) 走到i時 已經有j個不同pair 現在是選or不選可以有的最長長度? 狀態過多遞歸MLE
        這題要以值域去做思考 畢竟是相鄰相關，
        走到nums[i] = x時 至多有j個不同pair能有的最大長度
        f[x][j] = max(f[x][j] + 1, f[y][j-1] + 1) 並且枚舉選哪個 否則MLE
        '''
        n = len(nums)
        ans = 1
        # 空間優化
        f = [1] * n
        mp = defaultdict(int)
        for i in range(n):
            mp[nums[i]] += 1
            f[i] = mp[nums[i]]
            if f[i] > ans:
                ans = f[i]
        for t in range(1,k+1):
            mp = defaultdict(int)
            mp[nums[0]] = 1
            mx, num = 1, nums[0]
            for i in range(1,n):
                prev = f[i]
                f[i] = mx + 1 if mx + 1 > mp[nums[i]] + 1 else mp[nums[i]] + 1
                if f[i] > ans:
                    ans = f[i]
                if prev > mx:
                    mx = prev
                    num = nums[i]
                mp[nums[i]] = f[i]
        return ans
        '''
        遞推 TC:O(n * k) SC:O(n * k)
        # 因為n^2 * k做法每次都是在某個k次數狀況下往前看i之前最大值 所以這樣設計, 就可以控制成上一輪的最大值與當前該數字出現次數最大值取最大
        f = [[1] * n for _ in range(k+1)]
        mp = defaultdict(int)
        for i in range(n):
            mp[nums[i]] += 1
            f[0][i] = mp[nums[i]]
            if f[0][i] > ans:
                ans = f[0][i]
        for t in range(1,k+1):
            mp = defaultdict(int)
            mp[nums[0]] = 1
            mx, num = 1, nums[0]
            for i in range(1,n):
                f[t][i] = max(mx + 1, mp[nums[i]] + 1)
                if f[t][i] > ans:
                    ans = f[t][i]
                if f[t-1][i] > mx:
                    mx = f[t-1][i]
                    num = nums[i]
                mp[nums[i]] = f[t][i]
        return ans
        '''
        

        # 以下為3176 可通過做法 TC:O(n * n * k)
        '''
        遞推 枚舉選哪個
        ans = 1
        for i in range(1, n):
            # 枚舉選哪個
            for j in range(i-1, -1, -1):
                for t in range(min(k+1, j+1)):
                    if nums[i] == nums[j]:
                        f[i][t] = max(f[i][t], f[j][t] + 1)
                        ans = max(ans, f[i][t])
                    else:
                        if t + 1 <= k:
                            f[i][t+1] = max(f[i][t+1], f[j][t] + 1)
                            ans = max(ans, f[i][t+1])
        return ans
        '''
        '''
        遞歸 不能選or不選 狀態過多 MLE 改枚舉選哪個節省一個狀態
        @cache
        def dfs(i:int, cnt:int) -> int:
            if i < 0:
                return 0
            if i + 1 <= k - cnt:
                return i + 1
            ans = 1
            for j in range(i-1, -1, -1):
                if nums[i] == nums[j]:
                    ans = max(ans, dfs(j, cnt) + 1)
                else:
                    if cnt + 1 <= k:
                        ans = max(ans, dfs(j, cnt + 1) + 1)
            return ans
        # dfs.cache_clear()
        return max(dfs(i, 0) for i in range(n))
        '''
