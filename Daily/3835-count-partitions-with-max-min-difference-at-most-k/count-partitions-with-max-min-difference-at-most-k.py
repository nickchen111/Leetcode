class Solution:
    def countPartitions(self, nums: List[int], k: int) -> int:
        '''
        區間差k 用monotonic queue sliding window做
        設計一個DP 表示 走到i當作結尾可以組成的合法array有多少個
        這之間的總和就是用prefix sum做
        '''
        n = len(nums)
        MOD = 10 ** 9 + 7
        f = [1] * (n + 1)
        pre = 1
        mn = deque()
        mx = deque()
        i = 0
        for j, x in enumerate(nums):
            while mx and nums[mx[-1]] <= x:
                mx.pop()
            while mn and nums[mn[-1]] >= x:
                mn.pop()
            mx.append(j)
            mn.append(j)
            while nums[mx[0]] - nums[mn[0]] > k:
                if mx[0] == i:
                    mx.popleft()
                if mn[0] == i:
                    mn.popleft()
                pre -= f[i] % MOD
                i += 1
            f[j + 1] = pre % MOD
            pre += f[j + 1] % MOD

        return f[n]
