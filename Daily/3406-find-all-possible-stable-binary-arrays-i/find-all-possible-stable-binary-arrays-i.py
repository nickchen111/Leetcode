class Solution:
    def numberOfStableArrays(self, zero: int, one: int, limit: int) -> int:
        '''
        greater than limit -> limit + 1長度必須都要有0 and 1
        '''
        MOD = 10 ** 9 + 7
        dp = [[[0] * 2 for _ in range(one + 1)] for _ in range(zero + 1)]
        pre = [[[0] * 2 for _ in range(one + 1)] for _ in range(zero + 1)]

        dp[0][0][0] = dp[0][0][1] = 1
        pre[0][0][0] = pre[0][0][1] = 1

        for i in range(zero + 1):
            for j in range(one + 1):
                if i == 0 and j == 0:
                    continue
                # 只要 i - limit - 1 >= 0 即可 x x x x x limit = 3
                dp[i][j][0] = ((pre[i - 1][j][1] if i - 1 >= 0 else 0) - (pre[i - limit - 1][j][1] if i - limit - 1 >= 0 else 0)) % MOD
                dp[i][j][1] = ((pre[i][j - 1][0] if j - 1 >= 0 else 0) - (pre[i][j - limit - 1][0] if j - limit - 1 >= 0 else 0)) % MOD
                pre[i][j][0] = ((pre[i][j - 1][0] if j - 1 >= 0 else 0) + dp[i][j][0]) % MOD
                pre[i][j][1] = ((pre[i - 1][j][1] if i - 1 >= 0 else 0) + dp[i][j][1]) % MOD
        return (dp[zero][one][0] + dp[zero][one][1]) % MOD
