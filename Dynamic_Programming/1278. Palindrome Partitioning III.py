# TC:O(n^2 * k) SC:O(n^2 + n * k)
class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        '''
        首先我會想知道某一段要變成回文串需要換幾次?
        下一步我就可以用劃分型DP的方式把字串切斷判斷哪種分割方式需要替換的次數比較少
        劃分型DP: 斷在某個地方並且後面還剩下多少組所需的最小替換次數
        '''
        n = len(s)
        minChange = [[inf] * (n) for _ in range(n)]
        for i in range(n):
            minChange[i][i] = 0
            if i + 1 < n:
                minChange[i][i+1] = 0 if s[i] == s[i+1] else 1
        
    
        for i in range(n-3, -1, -1):
            for j in range(i + 2, n):
                minChange[i][j] = minChange[i+1][j-1] + ( 1 if s[i] != s[j] else 0)
        f = [[inf] * (k+1) for _ in range(n+1)]
        f[0][0] = 0
        for i in range(n):
            for cnt in range(k):
                for j in range(i, cnt-2, -1):
                    f[i+1][cnt+1] = min(f[i+1][cnt+1], minChange[j][i] + f[j][cnt])
        return f[n][k]
        '''
        遞歸
        @cache
        def minChange(i:int, j:int) -> int:
            if i >= j:
                return 0
            return minChange(i + 1, j - 1) + (1 if s[i] != s[j] else 0)
        @cache
        def dfs(i:int, cnt:int) -> int:
            if i < 0 and cnt == 0:
                return 0
            if i < 0 or cnt == 0:
                return inf
            ans = inf
            # 需要留下後面還需要切割的最少組數 cnt = 2 代表之後只需要一組
            for j in range(i, cnt - 2, -1):
                ans = min(ans, minChange(j, i) + dfs(j-1, cnt-1))
            return ans
        return dfs(n-1, k)
        '''
  # 不同的定義 快許多 切割k-1刀，在s[:r] 範圍內最小需要的替換數量
  class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        n = len(s)
        min_change = [[0] * n for _ in range(n)]
        for i in range(n - 2, -1, -1):
            for j in range(i + 1, n):
                min_change[i][j] = min_change[i + 1][j - 1] + (1 if s[i] != s[j] else 0)

        f = [[0] * n for _ in range(k)]
        f[0] = min_change[0]  # 無需 copy
        for i in range(1, k):
            for r in range(i, n - (k - 1 - i)):  # 右邊還有 k−1−i 個子串 後面不用走 沒意義
                f[i][r] = min(f[i - 1][l - 1] + min_change[l][r] for l in range(i, r + 1))
        return f[-1][-1]
