class Solution:
    def maxOperations(self, s: str) -> int:
        ones = 0
        i = ans = 0
        while i < len(s):
            if s[i] == '1':
                ones += 1
            else:
                j = i
                while j < len(s) and s[j] == '0':
                    j += 1
                i = j - 1
                ans += ones
            i += 1
        return ans

