# TC:O(n^2 * k) SC:O(n*k)
class Solution:
    def largestSumOfAverages(self, nums: List[int], k: int) -> float:
        n = len(nums)
        f = [[float(-inf)] * (k+1) for _ in range(n+1)]
        f[0][0] = 0
        for i in range(n):
            sum = 0
            for t in range(i, -1, -1):
                sum += nums[t]
                for j in range(k):
                    if sum / (i - t + 1) + f[t][j] > f[i+1][j+1]:
                        f[i+1][j+1] = sum / (i - t + 1) + f[t][j]
        return f[n][k]
                    

        '''
        @cache
        def dfs(i:int, cnt:int) -> float:
            if i < 0 and cnt == 0:
                return 0.0
            if cnt == 0 or i < 0:
                return float(-inf)
            sum, ans = 0, 0
            for j in range(i, -1, -1):
                sum += nums[j]
                ans = max(ans, sum / (i - j + 1) + dfs(j - 1, cnt - 1))
            return ans
        return dfs(n-1, k)
        '''
