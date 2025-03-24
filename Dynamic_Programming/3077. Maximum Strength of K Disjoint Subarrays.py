# TC:O(n*k) SC:O(n)
class Solution:
    def maximumStrength(self, nums: List[int], k: int) -> int:
        '''
        k是odd 代表遇到 k = odd 就是+ even 就是- (k - groups + 1)
        k == 0 就回傳 0
        所以改成走到每一個就判斷一下是要加入之前的體系還是自成一格(j + 1)
        f[k][n] 分成i份以後 前j個數字可以達到的最大總和
        f[i][j] = f[i][j-1](不選), max(f[i-1][j-1] + (s[j] - s[L]) * w_i)
        '''
        n = len(nums)
        s = list(accumulate(nums, initial = 0))
        # 空間優化
        f = [0] * (n + 1)
        for i in range(1, k+1):
            # 最少需要有i個這樣之前才能有i-1組 然後還需要考慮後面要組成的組數 (k - i) 組 要剩下這麼多  n - (k - i) + 1
            pre = f[i-1]
            f[i-1] = mx = -inf
            w = (k - i + 1) * (1 if i % 2 else -1)
            for j in range(i, n - k + i + 1):
                mx = max(mx, pre - s[j-1] * w) # 主要推導公式的時候發現 (s[j] - s[L]) * w_i 可以拆出來
                pre = f[j]
                f[j] = max(f[j-1], s[j] * w + mx)
        return f[n]
        '''
        f = [[0] * (n + 1) for _ in range(k + 1)]
        
        for i in range(1, k+1):
            f[i][i-1] = mx = -inf
            # 最少需要有i個這樣之前才能有i-1組 然後還需要考慮後面要組成的組數 (k - i) 組 要剩下這麼多  n - (k - i) + 1
            w = (k - i + 1) * (1 if i % 2 else -1)
            for j in range(i, n - k + i + 1):
                mx = max(mx, f[i-1][j-1] - s[j-1] * w) # 主要推導公式的時候發現 (s[j] - s[L]) * w_i 可以拆出來
                f[i][j] = max(f[i][j-1], s[j] * w + mx)
        return f[k][n]
        '''
                
        


