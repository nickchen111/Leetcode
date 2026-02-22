# TC:O(n) SC:O(1)
class Solution:
    def maximumXor(self, s: str, t: str) -> str:
        '''
        就是按照s的0101搭配出相反數字即可
        '''
        cnt0 = t.count('0')
        left = [cnt0, len(t) - cnt0]
        ans = list(s)
        for i, ch in enumerate(s):
            x = int(ch)
            if left[x ^ 1] > 0:
                left[x ^ 1] -= 1
                ans[i] = '1'
            else:
                left[x] -= 1
                ans[i] = '0'
        return ''.join(ans)
