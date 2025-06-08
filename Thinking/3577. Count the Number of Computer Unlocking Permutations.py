# TC:O(n) SC:O(1)
N = 100001
MOD = 10 ** 9 + 7
fac = [0] * (N + 1)
fac[0] = 1
for i in range(1, N + 1):
    fac[i] = fac[i - 1] * i % MOD
class Solution:
    def countPermutations(self, complexity: List[int]) -> int:
        '''
        可以用任意較小數字開鎖 問說可以打開的permutation
        第一個鎖必須是最小的 接下來後面就隨便開了!?
        (n - 1) !
        '''
        n = len(complexity)
        for i in range(1, n):
            if complexity[i] <= complexity[0]:
                return 0
        return fac[n - 1]
            
