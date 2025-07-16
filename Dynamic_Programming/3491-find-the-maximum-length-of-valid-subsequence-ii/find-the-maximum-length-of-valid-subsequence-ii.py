class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        '''
        LIS 有k個DP就不能優化到O(1)空間做
        dp[i][j] 走到i為止以j為 % k 最長符合條件的長度
        '''
        n = len(nums)
        dp = [[1] * k for _ in range(n)]
        ans = 2
        for i in range(1, n):
            for j in range(0, i):
                mod = (nums[i] + nums[j]) % k
                if dp[j][mod] + 1 > dp[i][mod]:
                    dp[i][mod] = dp[j][mod] + 1
                    ans = max(ans, dp[i][mod])
        return ans
            
        return ans
