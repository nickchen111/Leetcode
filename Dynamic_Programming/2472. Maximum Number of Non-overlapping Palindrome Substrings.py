# TC:O(n^2) SC:O(n^2) Manacher可以做到O(n)
class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        '''
        選擇不重疊的substring 必須長度至少k, 每個都是回文串 -> 區間DP
        最多可以選幾個substring -> 不重疊就需要去根據選擇的string劃分
        '''
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = True
            if i + 1 < n:
                dp[i][i+1] = True if s[i] == s[i+1] else False
        for i in range(n-2, -1, -1):
            for j in range(i + 2, n):
                if s[i] == s[j] and dp[i+1][j-1]:
                    dp[i][j] = True
        f = [0] * (n+1)
        for i in range(n):
            if i < k-1:
                continue
            f[i+1] = f[i]
            for j in range(i - k + 1, -1, -1):
                if dp[j][i]:
                    f[i+1] = max(f[i+1], f[j] + 1)
        return f[n]
        

# 中心回文串判定法 可以做到 one pass
class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        n = len(s)
        f = [0] * (n + 1)
        for i in range(2 * n - 1):
            l, r = i // 2, (i + 1) // 2
            f[l + 1] = max(f[l + 1], f[l])
            while l >= 0 and r < n and s[l] == s[r]:
                if r - l + 1 >= k:
                    f[r + 1] = max(f[r + 1], f[l] + 1)
                    break
                l -= 1
                r += 1
        return f[n]

        
