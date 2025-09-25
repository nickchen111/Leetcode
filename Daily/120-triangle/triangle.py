class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        dp = [inf] * n
        dp[0] = triangle[0][0]
        for i in range(1, n):
            tmp = [inf] * n
            m = len(triangle[i])
            for j in range(m):
                tmp[j] = min(tmp[j], (dp[j] if j < i + 1 else inf) + triangle[i][j])
                if j + 1 < m:
                    tmp[j + 1] = min(tmp[j + 1], (dp[j] if j < i + 1 else inf) + triangle[i][j + 1])
            dp = tmp
        # print(dp)
        return min(dp[i] for i in range(n))
