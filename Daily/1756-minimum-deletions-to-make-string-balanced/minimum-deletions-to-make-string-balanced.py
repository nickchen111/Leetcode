class Solution:
    def minimumDeletions(self, s: str) -> int:
        '''
        需要判斷前面後面還有多少個a or b 
        要構造 ex aaaa or bbbb or aaaabbb
        '''
        n = len(s)
        suf = [0] * n
        cnt = 0
        for i in range(n - 1, -1, -1):
            suf[i] = cnt
            cnt += 1 if s[i] == 'a' else 0
        ans = min(n - cnt, cnt)
        cnt = 0
        for i in range(n):
            ans = min(ans, suf[i] + cnt)
            cnt += 1 if s[i] == 'b' else 0
        return ans