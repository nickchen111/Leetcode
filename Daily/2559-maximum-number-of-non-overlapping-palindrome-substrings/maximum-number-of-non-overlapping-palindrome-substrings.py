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