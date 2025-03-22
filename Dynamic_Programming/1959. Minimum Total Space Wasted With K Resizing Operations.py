# TC:O(n * k * n) SC:O(n * k)
class Solution:
    def minSpaceWastedKResizing(self, nums: List[int], k: int) -> int:
        '''
        可以變換的概念有點類似將目前的數組分段，等於每段中都要找到該段最大的元素 然後去計算 mx * len - sum(subarray)的總和
        這可以用前綴和來解
        '''
        n = len(nums)
        f = [[inf] * (k + 1) for _ in range(n + 1)]
        f[0][0] = 0
        mx, tot = -inf, 0
        for i in range(n):
            if nums[i] > mx: mx = nums[i]
            tot += nums[i]
            f[i+1][0] = mx * (i + 1) - tot
        for i in range(n):
            groups = i + 1
            if k < groups: groups = k # 前面可以組成幾組
            for j in range(0, groups):
                mx, tot = -inf, 0
                for t in range(i, -1, -1):
                    if t + 1 < j: break # 預先停止 如果使用的組數少於目前預測前面可以組成的數量就直接break
                    if nums[t] > mx: mx = nums[t]
                    tot += nums[t]
                    if f[t][j] + mx * (i - t + 1) - tot < f[i+1][j+1]:
                        f[i+1][j+1] = f[t][j] + mx * (i - t + 1) - tot
        return f[n][k]

        '''
        遞歸
        @cache 
        def dfs(i:int, j:int):
            if i < 0:
                return 0
            if j == 0:
                return max(nums[:i+1]) * (i + 1) - sum(nums[:i+1])
            ans, mx = inf, -inf
            cur_sum = 0
            for t in range(i, -1, -1):
                if nums[t] > mx: mx = nums[t]
                cur_sum += nums[t]
                nxt = dfs(t - 1, j - 1)
                if nxt + mx * (i - t + 1) - cur_sum < ans: ans = nxt + mx * (i - t + 1) - cur_sum
            return ans
        return dfs(n-1, k)
        '''
        

        '''
        Presum + 遞歸
        presum = [0] + list(accumulate(nums))
        # print(presum)
        @cache 
        def dfs(i:int, j:int):
            if i == n:
                return 0
            if j == k:
                return max(nums[i:n]) * (n - i) - (presum[n] - presum[i])
            ans, mx = inf, -inf
            for t in range(i, n):
                if nums[t] > mx: mx = nums[t]
                nxt = dfs(t + 1, j + 1)
                if nxt + mx * (t - i + 1) - (presum[t+1] - presum[i]) < ans: ans = nxt + mx * (t - i + 1) - (presum[t+1] - presum[i])
            return ans
        return dfs(0, 0)
        '''
