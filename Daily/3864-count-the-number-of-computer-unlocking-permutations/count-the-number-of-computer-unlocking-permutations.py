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
        def fac(x:int) -> int:
            if x == 1:
                return 1
            return x * fac(x - 1)
        return fac(n - 1) % MOD
        
