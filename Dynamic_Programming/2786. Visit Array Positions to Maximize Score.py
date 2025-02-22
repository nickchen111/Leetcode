class Solution:
    def maxScore(self, nums: List[int], x: int) -> int:
        n = len(nums)
        # 空間優化
        odd = nums[0] if (nums[0] % 2) else -inf
        even = nums[0] if (nums[0] % 2) == 0 else -inf
        for i in range(1, n):
            if nums[i] % 2:
                odd = max(odd, even - x) + nums[i]
            else:
                even = max(even, odd - x) + nums[i]
        return max(odd, even)
        '''
        遞推
        f = [[-inf] * 2 for _ in range(n)]
        f[0][nums[0] % 2] = nums[0]
        for i in range(1, n):
            f[i][nums[i] % 2] = max(f[i-1][nums[i] % 2], f[i-1][1 - (nums[i] % 2)] - x) + nums[i]
            f[i][1 - nums[i] % 2] = f[i-1][1 - nums[i] % 2]
        return max(f[n-1][0], f[n-1][1])
        '''
        '''
        遞歸
        @cache
        def dfs(i: int, parity: int) -> int:
            if i == n:
                return 0
            ans = dfs(i + 1, parity)
            ans = max(ans, dfs(i + 1, nums[i] % 2) + nums[i]) if nums[i] % 2 == parity else max(ans, dfs(i + 1, nums[i] % 2) + nums[i] - x)
            return ans
        return nums[0] + dfs(1, nums[0] % 2)
        '''
