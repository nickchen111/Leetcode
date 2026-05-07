class Solution:
    def maxValue(self, nums: List[int]) -> List[int]:
        '''
        往前只能變大 往後只能變小
        '''
        n = len(nums)
        pre_max = list(accumulate(nums, max))
        suf_min = inf
        ans = [0] * n
        for i in range(n - 1, -1, -1):
            ans[i] = pre_max[i] if pre_max[i] <= suf_min else ans[i + 1]
            suf_min = min(suf_min, nums[i])
        return ans