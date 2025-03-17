# TC:O(n^2) SC:O(n) -> O(k)
class Solution:
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:
        '''
        劃分型DP, 讓最大值代表他 * 長度 至多k就一定得切割
        '''
        # 空間優化
        n = len(arr)
        n = len(arr)
        f = [0] * k
        for i in range(n):
            res = mx = 0
            for j in range(i, max(i - k, -1), -1):
                mx = max(mx, arr[j])
                res = max(res, f[j % k] + (i - j + 1) * mx)
            f[(i + 1) % k] = res
        return f[n % k]
        '''
        遞推
        f = [0] * (n+1)
        for i in range(n):
            mx = 0
            for j in range(i, max(-1, i - k), -1):
                mx = max(mx, arr[j])
                f[i+1] = max(f[i+1], mx * (i - j + 1) + f[j]) 
        return f[n]
        '''
        '''
        @cache
        def dfs(i:int) -> int:
            if i < 0:
                return 0
            mx, ans = -inf, -inf
            for j in range(i, max(-1, i - k), -1):
                mx = max(mx, arr[j])
                ans = max(ans, dfs(j-1) + mx * (i - j + 1))
            return ans
        return dfs(len(arr) - 1)
        '''
                
