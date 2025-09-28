#TC:O(n) SC:O(1)
class Solution:
    def climbStairs(self, n: int, costs: List[int]) -> int:
        '''
        從0開始跳 要跳到n 每次只能跳 i + 1, i + 2, i + 3
        cost代價是個公式
        '''
        # 空間優化
        dp, prev1, prev2, prev3 = inf, 0 ,inf, inf
        for i in range(1, n + 1):
            dp = min(prev1 + costs[i - 1] + 1, prev2 + costs[i - 1] + 4, prev3 + costs[i - 1] + 9)
            prev1, prev2, prev3 = dp, prev1, prev2
        return dp

        '''
        # 遞推
        dp = [inf] * (n + 1)
        dp[0] = 0
        for i in range(1, n + 1):
            for j in range(i - 1, max(-1, i - 4), -1):
                dp[i] = min(dp[i], dp[j] + costs[i - 1] + (i - j) * (i - j))
        return dp[n]
        '''
        '''
        遞歸
        @cache
        def dfs(i:int) -> int:
            if i == 0:
                return 0
            if i < 0:
                return inf
            return min(dfs(i - 1) + costs[i - 1] + 1, dfs(i - 2) + costs[i - 1] + 4, dfs(i - 3) + costs[i - 1] + 9)
        return dfs(n)
        '''
