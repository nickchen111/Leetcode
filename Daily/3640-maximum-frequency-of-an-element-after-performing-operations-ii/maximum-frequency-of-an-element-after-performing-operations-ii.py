class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        # 枚舉每個數字當作是中心 +-k 去看有多少個 超過numoperations 就取到上線
        nums.sort()
        cnt = Counter(nums)
        ans = 0
        for x in nums:
            i = bisect_left(nums, x - k)
            j = bisect_right(nums, x + k)
            if j - i - cnt[x] > numOperations:
                ans = max(ans, numOperations + cnt[x])
            else:
                ans = max(ans, j - i)
        for x in nums:
            i = bisect_left(nums, x)
            j = bisect_right(nums, x + 2 * k)
            if j - i > numOperations:
                ans = max(ans, numOperations)
            else:
                ans = max(ans, j - i)
        return ans