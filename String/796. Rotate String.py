# TC:O(n) SC:O(n)
class Solution:
    def rotateString(self, s: str, goal: str) -> bool:
        def kmp_search(text:str, pattern:str) -> int:
            m = len(pattern)
            lsp = [0] * m
            for i in range(1, m):
                j = lsp[i - 1]
                while j > 0 and pattern[j] != pattern[i]:
                    j = lsp[j - 1]
                lsp[i] = j + (1 if pattern[j] == pattern[i] else 0)
            n = len(text)
            dp = [0] * n
            dp[0] = 1 if text[0] == pattern[0] else 0
            cnt = 0
            for i in range(1, n):
                j = dp[i - 1]
                if j == m:
                    j = lsp[j - 1]
                while j > 0 and pattern[j] != text[i]:
                    j = lsp[j - 1]
                dp[i] = j + (1 if pattern[j] == text[i] else 0)
                if dp[i] == len(pattern):
                    cnt += 1
            return cnt
        return len(s) == len(goal) and kmp_search(s + s, goal) > 0
