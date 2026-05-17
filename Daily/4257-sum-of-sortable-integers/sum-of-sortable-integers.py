class Solution:
    def sortableIntegers(self, nums: List[int]) -> int:
        n = len(nums)
        next_dec = [0] * n  # nums[next_dec[i]] > nums[next_dec[i] + 1]
        next_dec[-1] = p = n
        # 对于每个 i，记录下一个递减的位置
        for i in range(n - 2, -1, -1):
            if nums[i] > nums[i + 1]:
                p = i
            next_dec[i] = p

        def solve(k: int) -> None:
            last_max = 0  # 上一段的最大值
            for r in range(k - 1, n, k):
                l = r - k + 1
                m = next_dec[l]
                if m >= r:
                    # [l, r] 是递增的，最小值为 nums[l]，最大值为 nums[r]
                    # 最小值必须 >= 上一段的最大值
                    if nums[l] < last_max:
                        return
                    last_max = nums[r]
                else:
                    # [l, m] 是第一段，[m+1, r] 是第二段
                    # 第二段必须是递增的，且第二段的最小值必须 >= 上一段的最大值，且第二段的最大值必须 <= 第一段的最小值
                    if next_dec[m + 1] < r or nums[m + 1] < last_max or nums[r] > nums[l]:
                        return
                    last_max = nums[m]
            nonlocal ans
            ans += k  # 满足要求

        ans = 0
        # 枚举 n 的因子 k
        for k in range(1, isqrt(n) + 1):
            if n % k == 0:
                solve(k)
                if k * k < n:
                    solve(n // k)
        return ans