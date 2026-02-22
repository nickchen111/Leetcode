# TC:O(logn) SC:O(1)
MAX_NUM = 10
fac = [1] * (MAX_NUM + 1)
for i in range(MAX_NUM):
    fac[i + 1] = fac[i] * (i + 1)
class Solution:
    def isDigitorialPermutation(self, n: int) -> bool:
        cur = n
        ans = 0
        cnt = [0] * 10
        while cur:
            cur, d = divmod(cur, 10)
            ans += fac[d]
            cnt[d] += 1
        while ans > 0:
            ans, d = divmod(ans, 10)
            cnt[d] -= 1
        return cnt == [0] * 10
        
