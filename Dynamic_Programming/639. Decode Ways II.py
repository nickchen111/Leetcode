# TC:O(n) SC:O(n)
class Solution:
    def numDecodings(self, s: str) -> int:
        MOD = 10 ** 9 + 7
        n = len(s)
        dp = [0] * (n + 1)
        dp[n] = 1 
        
        for i in range(n - 1, -1, -1):
            if s[i] == '0': dp[i] = 0
            else: dp[i] = 9 * dp[i+1]  % MOD if s[i] == '*' else dp[i+1]  % MOD

            if i + 1 < n:
                if s[i] != '*' and s[i+1] != '*':
                    num = (ord(s[i]) - ord('0')) * 10 + (ord(s[i+1]) - ord('0'))
                    if 10 <= num <= 26:
                        dp[i] = (dp[i] + dp[i+2]) % MOD
                elif s[i] == '*' and s[i+1] == '*':
                    dp[i] = (dp[i] + 15 * dp[i+2]) % MOD
                elif s[i] == '*' and s[i+1] != '*':
                    dp[i] = (dp[i] + 2 * dp[i+2]) % MOD if '0' <= s[i+1] <= '6' else (dp[i] + dp[i+2]) % MOD
                elif s[i] != '*' and s[i+1] == '*':
                    if s[i] == '1':
                        dp[i] = (dp[i] + 9 * dp[i+2]) % MOD
                    elif s[i] == '2':
                        dp[i] = (dp[i] + 6 * dp[i+2]) % MOD
        return dp[0] % MOD

        '''
        遞歸
        @cache
        def dfs(i: int) -> int:
            if i == n:
                return 1
            if s[i] == '0':
                return 0
            ans = dfs(i+1) * 9 if s[i] == '*' else dfs(i+1)
            if i + 1 < n:
                next2 = dfs(i+2)
                if s[i] != '*' and s[i+1] != '*':
                    num = (ord(s[i]) - ord('0')) * 10 + (ord(s[i+1]) - ord('0'))
                    if 10 <= num <= 26:
                        ans += next2
                elif s[i] == '*' and s[i+1] == '*':
                    ans += next2 * 15
                elif s[i] == '*' and s[i+1] != '*':
                    ans += 2 * next2 if '0' <= s[i+1] <= '6' else next2
                elif s[i] != '*' and s[i+1] == '*':
                    if s[i] == '1':
                        ans += 9 * next2
                    elif s[i] == '2':
                        ans += 6 * next2
            return ans % MOD
        # dfs.cache_clear()
        return dfs(0) % MOD
        '''
