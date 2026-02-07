class Solution:
    def minimumDeletions(self, s: str) -> int:
        '''
        需要判斷前面後面還有多少個a or b 
        要構造 ex aaaa or bbbb or aaaabbb
        '''
        n = len(s)
        suf_a = [0] * (n + 1)
        suf_b = [0] * (n + 1)
        cnt_a = cnt_b = pre_a = pre_b = 0
        for i in range(n - 2, -1, -1):
            suf_a[i] = suf_a[i + 1] + (1 if s[i + 1] == 'a' else 0)
            suf_b[i] = suf_b[i + 1] + (1 if s[i + 1] == 'b' else 0)
        ans = inf
        for i in range(n):
            if s[i] == 'a':
                ans = min(ans, pre_b + min(suf_a[i], suf_b[i]), pre_a + 1 + suf_a[i])
                pre_a += 1
            else:
                ans = min(ans, pre_b + 1 + suf_b[i], pre_a + suf_a[i])
                pre_b += 1
        return ans