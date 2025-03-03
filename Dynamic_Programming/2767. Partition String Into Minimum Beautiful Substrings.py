# TC:O(n^2) SC:O(n)
class Solution:
    def minimumBeautifulSubstrings(self, s: str) -> int:
        n = len(s)
        st = {5 ** i for i in range(n+1)}
        f = [inf] * (n+1)
        f[0] = 0
        for i in range(n):
            if s[i] == '0': continue
            sum = 0
            for j in range(i,n):
                sum = sum * 2 + 1 if s[j] == '1' else sum * 2
                if sum in st:
                    f[j+1] = min(f[j+1], f[i] + 1)
        return f[n] if f[n] is not inf else -1
        '''
        @cache
        def dfs(i:int) -> int:
            if i == n:
                return 0
            if s[i] == '0':
                return inf
            ans = inf
            sum = 0
            for j in range(i, n):
                sum = sum * 2 + 1 if s[j] == '1' else sum * 2
                if sum in st:
                    ans = min(ans, dfs(j+1) + 1)
            return ans
        ans = dfs(0)
        return ans if ans is not inf else -1
        '''

            
