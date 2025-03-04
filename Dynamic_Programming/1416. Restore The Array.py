# TC:O(n * m) m 為 k的數字長度 SC:O(n)
class Solution:
    def numberOfArrays(self, s: str, k: int) -> int:
        '''
        no leading zero, 需要在k範圍內有多少的劃分方案
        '''
        MOD = 10 ** 9 + 7
        n = len(s)
        f = [0] * (n+1)
        f[n] = 1
        for i in range(n-1, -1, -1):
            if s[i] == '0':
                continue
            sum = 0
            for j in range(i, n):
                sum = sum * 10 + ord(s[j]) - ord('0')
                if sum <= k:
                    f[i] = (f[i] + f[j+1]) % MOD
                else:
                    break
        return f[0] % MOD

        '''
        @cache
        def dfs(i:int) -> int:
            if i == n:
                return 1
            if s[i] == '0':
                return 0
            sum = 0
            ans = 0
            for j in range(i, n):
                sum = sum * 10 + ord(s[j]) - ord('0')
                if sum <= k:
                    ans += dfs(j+1)
                else:
                    break
            return ans % MOD
        return dfs(0) % MOD
        '''
