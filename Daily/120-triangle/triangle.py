class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        dp = [inf] * n
        dp[0] = triangle[0][0]
        for i in range(1, n):
            tmp = [inf] * n
            m = len(triangle[i])
            for j in range(m - 1):
                tmp[j] = min(tmp[j], dp[j] + triangle[i][j])
                tmp[j + 1] = min(tmp[j + 1], dp[j] + triangle[i][j + 1])
            dp = tmp
        # print(dp)
        return min(dp[i] for i in range(n))
