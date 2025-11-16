# TC:O(n) SC:O(1)
class Solution:
    def numSub(self, s: str) -> int:
        MOD = 10 ** 9 + 7
        i = ans = 0
        n = len(s)
        while i < n:
            j = i
            while j < n and s[j] == '1':
                j += 1
                ans += j - i
            i = j + 1
        return ans % MOD
