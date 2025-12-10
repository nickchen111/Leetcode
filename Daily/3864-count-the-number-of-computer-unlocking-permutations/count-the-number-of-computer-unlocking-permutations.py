MOD = 10**9 + 7
facs = {}
facs[1] = 1
facs[2] = 2
for i in range(2,(10**5)+1):
    facs[i] = (facs[i-1] * i) % MOD

class Solution:
    def countPermutations(self, c: List[int]) -> int:
        '''
        i < j, c[i] < c[j] 可以開j
        一個電腦應該可以開很多台電腦 只要確定第一台是最小的那就可以開所有可能性的電腦
        '''
        MOD = 10 ** 9 + 7
        n = len(c)
        mn = c[0]
        for i in range(1,n):
            if c[i] <= mn:
                return 0
        return facs[n - 1]
        
