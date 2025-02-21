# 狀態機DP TC:O(n) SC:O(1)
class Solution:
    def numberOfWays(self, s: str) -> int:
        n = len(s)
        # 空間優化
        dp = [[0] * 4 for _ in range(2)]
        dp[0][0] = 1
        dp[1][0] = 1

        for i in range(n):
            building = int(s[i])
            prev0, prev1 = 0, 1
            for k in range(4):
                if k > 0:
                    if building == 1:
                        dp[building][k] += prev0
                    else:
                        dp[building][k] += prev1
                prev0 = dp[0][k]
                prev1 = dp[1][k]

        return dp[0][3] + dp[1][3]
        
        '''
        遞推
        dp = [[[0] * 4 for _ in range(2)] for _ in range(n+1)]
        dp[0][0][0] = 1
        dp[0][1][0] = 1

        for i in range(n):
            building = int(s[i])  # 0 或 1
            for k in range(4):
                dp[i+1][0][k] = dp[i][0][k]
                dp[i+1][1][k] = dp[i][1][k]
                if k > 0:
                    dp[i+1][building][k] += dp[i][1-building][k-1]

        return dp[n][0][3] + dp[n][1][3]  # 選擇 3 棟建築的總方式數量
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, j:int, k:int) -> int:
            if k == 3:
                return 1
            if i < 0:
                return 0
            ans = dfs(i-1, j, k) # 不選
            if j == -1 or j != int(s[i]):
                ans += dfs(i-1, int(s[i]), k+1)
            return ans
        return dfs(n-1, -1, 0)
        '''
# 前後綴分解 TC:O(n) SC:O(n)
class Solution:
    def numberOfWays(self, s: str) -> int:
        n = len(s)
        suffix0 = [0] * n
        suffix1 = [0] * n
        cnt1, cnt0 = 0, 0
        for i in range(n-1, -1, -1):
            cnt1 += s[i] == '1'
            cnt0 += s[i] == '0'
            suffix0[i], suffix1[i] = cnt0, cnt1
        cnt0, cnt1, ans = 0, 0, 0
        for i in range(n-1):
            if s[i] == '1':
                ans += cnt0 * suffix0[i]
                cnt1 += 1
            else:
                ans += cnt1 * suffix1[i]
                cnt0 += 1
        return ans
# 前綴和思想 TC:O(n) SC:O(1)
class Solution:
    def numberOfWays(self, s: str) -> int:
        ways = 0
        one = zero = zero_one = one_zero = 0
        for c in s:
            if c == '0':
                zero += 1
                one_zero += one
                ways += zero_one
            else:
                one += 1    
                zero_one += zero 
                ways += one_zero
        return ways
