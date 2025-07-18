class Solution:
    def minimumDifference(self, nums: List[int]) -> int:
        '''
        可以刪除n個元素 剩餘的 2 * n 個 左邊 - 右邊總和的最小值？
        可想而知後n個前段肯定取不到
        不太能貪心 應該要枚舉 -> DP?! 分前後段
        '''
        
        n = len(nums) // 3
        m = len(nums)
        left_min = [0] * m
        min_pq = []
        acc = 0
        for i in range(n):
            heappush(min_pq, -nums[i])
            acc += nums[i]
        left_min[n - 1] = acc
        for i in range(n, 2 * n):
            heappush(min_pq, -nums[i])
            acc += nums[i]
            acc += heappop(min_pq)
            left_min[i] = acc
        acc = 0
        max_pq = []
        right_max = [0] * m
        for i in range(m - 1, 2 * n - 1, -1):
            heappush(max_pq, nums[i])
            acc += nums[i]
        right_max[2*n] = acc
        for i in range(2 * n - 1, n - 1, -1):
            heappush(max_pq, nums[i])
            acc += nums[i]
            acc -= heappop(max_pq)
            right_max[i] = acc
        ans = inf
        for i in range(n - 1, 2 * n):
            ans = min(ans, left_min[i] - right_max[i + 1])
        return ans
        

