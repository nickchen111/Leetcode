# TC:O(n*k) SC:O(n*k)
class Solution:
    def beautifulPartitions(self, s: str, k: int, minLength: int) -> int:
        '''
        1. 切成k份
        2. 每一份最少minLength
        3. 開頭prime (2,3,5,7) 結尾非prime(1,4,6,8,9)
        '''
        MOD = 10 ** 9 + 7
        n = len(s)
        if n < k * minLength:
            return 0
        dp = [[0] * (n + 1) for _ in range(k + 1)]
        dp[0][0] = 1

        primeSet = {'2', '3', '5', '7'}
        for t in range(1, k + 1):
            cumulative = 0
            # i 表示切分後的前綴長度，至少要有 t * minLength 個字符
            for i in range(t * minLength, n + 1):
                if s[i - minLength] in primeSet:
                    cumulative += dp[t - 1][i - minLength]
                dp[t][i] = cumulative if s[i - 1] not in primeSet else 0
        return dp[k][n] % MOD

        '''
        @cache
        def dfs(i: int, cnt: int) -> int:
            if i < 0 and cnt == 0:
                return 1
            if i < 0 or cnt == 0:
                return 0
            endDigit = int(s[i])
            if endDigit not in nonPrimeSet:
                return 0
            ans = 0
            for j in range(i - minLength + 1, -1, -1):
                startDigit = int(s[j])
                if startDigit in primeSet:
                    ans = (ans + dfs(j - 1, cnt - 1)) % MOD
            return ans
        
        return dfs(n - 1, k) % MOD
        '''
