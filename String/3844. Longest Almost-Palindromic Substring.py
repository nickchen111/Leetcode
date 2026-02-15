# 中心擴展法 TC:O(n^2) SC:O(1)
class Solution:
    def almostPalindromic(self, s: str) -> int:
        n = len(s)
        ans = 0
        def expand(l:int, r:int) -> None:
            while l >= 0 and r < n and s[l] == s[r]:
                l -= 1
                r += 1
            nonlocal ans
            ans = max(ans, r - l - 1)
        
        for i in range(2 * n - 1): # 因為有 n 個中心點(odd) + (n - 1)個兩個一組中心點(偶數)
            l, r = i // 2, (i + 1) // 2
            while l >= 0 and r < n and s[l] == s[r]:
                l -= 1
                r += 1
            expand(l - 1, r)
            expand(l, r + 1)
            if ans >= n:
                return n
        return ans

# DP TC:O(n^2) SC:O(n^2)
class Solution:
    def almostPalindromic(self, s: str) -> int:
        n = len(s)
        dp0 = [[False] * n for _ in range(n)]
        dp1 = [[False] * n for _ in range(n)]
        for i in range(n - 2, -1, -1):
            dp0[i][i] = True
            if i + 1 < n:
                dp0[i][i + 1] = True if s[i] == s[i + 1] else False
                dp1[i][i + 1] = True 

            for j in range(i + 2, n):
                if s[i] == s[j]:
                    dp0[i][j] = dp0[i + 1][j - 1]
                    dp1[i][j] = dp0[i + 1][j - 1] or dp1[i + 1][j - 1]
                else:
                    dp0[i][j] = False
                    dp1[i][j] = dp0[i + 1][j] or dp0[i][j - 1]
        
        max_len = 0
        for i in range(n):
            for j in range(i + 1, n):
                if dp1[i][j]:
                    max_len = max(max_len, j - i + 1)
        
        return max_len
