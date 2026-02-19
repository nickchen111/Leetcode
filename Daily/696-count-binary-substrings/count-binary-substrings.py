class Solution:
    def countBinarySubstrings(self, s: str) -> int:
        '''
        前後字串取最小長度
        '''
        pre = i = ans = 0
        n = len(s)
        while i < n:
            j = i
            while j < n and s[i] == s[j]:
                j += 1
            ans += min(pre, j - i)
            pre = j - i
            i = j
        return ans