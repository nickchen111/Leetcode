class Solution:
    def findTheString(self, lcp: List[List[int]]) -> str:
        n = len(lcp)
        s = [''] * n
        i = 0
        for c in ascii_lowercase:
            for j in range(i, n):
                if lcp[i][j]:
                    s[j] = c
            while i < n and s[i]:
                i += 1
            if i == n:
                break

        if i < n:
            return ""

        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                actual_lcp = 0 if s[i] != s[j] else (1 if i == n - 1 or j == n - 1 else lcp[i + 1][j + 1] + 1)
                if lcp[i][j] != actual_lcp:
                    return ""
        return ''.join(s)
