# TC:O(n^2 * k + n^3 * logn) SC:O(n^2)
class Solution:
    def minimumChanges(self, s: str, k: int) -> int:
        '''
        劃分型DP, 兩個狀態, 從i開始往回推，還剩下j組要分，可以分出的需要修改為半回文串的最少數量總和是多少
        裡面可以在for loop 判斷劃分點
        判斷分出來的子串是否滿足條件 
        1. 是否是回文串 abccba 可以用 d = 1 去除 肯定可以
        2. 對每個長度做 因式分解找他的 需要sqrt(len) 針對每個長度判斷
           for len = 因式分解出來的數字長度
                將下標字串拼湊出來並且判斷是否都吻合回文串 O(n) 如果不符合需要修改多少次 之後加總這個長度的次數 判斷每個長度最小值是多少
        '''
        n = len(s)
        factor = [[] for _ in range(n+1)] # 因式分解 每個長度 -> 因式
        for l in range(1, n+1 // 2): # 小優化 // 2 反正後面的for loop 都會不過
            for j in range(l*2, n+1, l):
                factor[j].append(l)

        def get_modify(t:str) -> int:
            m = len(t)
            min_cnt = inf
            # O(nlogn)
            for d in factor[m]:
                cnt = 0
                for i in range(d):
                    # 例如目前餘數是希望要index 1 總長度為 m = 15(1,2,3,5)的話 0 1 2 3 4 0 1 2 3 4 0 1 2 3 4按照 l = 5 分組 (m / l) *  + i
                    left, right = i, m - d + i
                    while left < right:
                        if t[left] != t[right]:
                            cnt += 1
                        left += d
                        right -= d
                if cnt < min_cnt: min_cnt = cnt
            return min_cnt
        modify = [[inf] * n for _ in range(n)]
        for i in range(n-1):
            tmp = s[i]
            for j in range(i+1, n):
                tmp += s[j]
                modify[i][j] = get_modify(tmp)
        # 遞推 + 空間優化
        f = modify[0]
        for i in range(1, k):
            for j in range(n - 1 - (k - 1 - i) * 2, i * 2, -1):
                f[j] = min(f[L - 1] + modify[L][j] for L in range(i * 2, j))
        return f[-1]
        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int:
            if i == 0: return modify[0][j]
            ans = inf 
            for t in range(i*2, j): # 假設剩下1組 他後面必須還要有 len = 2 所以最多到 j = 1
                tmp = dfs(i - 1, t - 1) + modify[t][j]
                if tmp < ans:
                    ans = tmp
            return ans
        return dfs(k-1, n-1)
        '''

  # 剛開始自己過的時候還沒修的寫法 邏輯稍微不同 但大同小異
  class Solution:
    def minimumChanges(self, s: str, k: int) -> int:
        '''
        劃分型DP, 兩個狀態, 從i開始往回推，還剩下j組要分，可以分出的需要修改為半回文串的最少數量總和是多少
        裡面可以在for loop 判斷劃分點
        判斷分出來的子串是否滿足條件 
        1. 是否是回文串 abccba 可以用 d = 1 去除 肯定可以
        2. 對每個長度做 因式分解找他的 需要sqrt(len) 針對每個長度判斷
           for len = 因式分解出來的數字長度
                將下標字串拼湊出來並且判斷是否都吻合回文串 O(n) 如果不符合需要修改多少次 之後加總這個長度的次數 判斷每個長度最小值是多少
        '''
        # 因式分解 每個長度 -> 因式
        n = len(s)
        factor = [[] for _ in range(n+1)]
        for l in range(1, n+1 // 2): # 小優化 // 2 反正後面的for loop 都會不過
            for j in range(l*2, n+1, l):
                factor[j].append(l)
        # 判斷每個區間所需要滿足題目條件的最少次數 區間dp去計算
        def helper(t:str, l:int) -> int:
            #能否直接按照餘數分組做雙指針判斷
            m = len(t)
            c = 0
            for i in range(l):
                # 例如目前餘數是希望要index 1 總長度為 m = 15(1,2,3,5)的話 0 1 2 3 4 0 1 2 3 4 0 1 2 3 4按照 l = 5 分組 (m / l) *  + i
                left, right = i, m - l + i
                while left < right:
                    if t[left] != t[right]:
                        c += 1
                    left += l
                    right -= l
            return c
        dp = [[inf] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = 0
            if i + 1 < n:
                if s[i] == s[i+1]: dp[i][i+1] = 0
                else: dp[i][i+1] = 1
                tmp = s[i] + s[i+1]
            for j in range(i+2, n):
                tmp += s[j]
                l = j - i + 1 # 目前長度
                min_cnt = inf
                for d in factor[l]: # sqrt(l)  大概 10 的數量級
                    cnt = helper(tmp, d)
                    if cnt < min_cnt:
                        min_cnt = cnt
                dp[i][j] = min_cnt
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0 and j == 0:
                return 0
            if i < 0 or j == 0:
                return inf
            ans = inf 
            for t in range(i-1, 2 * (j-1) - 1, -1): # 假設剩下1組 他後面必須還要有 len = 2 所以最多到 i = 1
                tmp = dfs(t - 1, j - 1) + dp[t][i]
                if tmp < ans:
                    ans = tmp
            return ans
        return dfs(n-1, k)
