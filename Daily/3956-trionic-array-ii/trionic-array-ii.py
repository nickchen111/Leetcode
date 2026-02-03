class Solution:
    def maxSumTrionic(self, nums: List[int]) -> int:
        '''
        找出他前後嚴格遞增段
        前面那段的話可以看最大到哪 後面那段就全取
        中間段必須是嚴格遞減
        '''
        n = len(nums)
        pre = [-inf] * n
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                pre[i] = max(pre[i - 1] + nums[i], nums[i] + nums[i - 1])
        suf = [-inf] * n
        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                suf[i] = max(nums[i + 1], suf[i + 1]) + nums[i]
        # 開始找遞減段
        i = 1
        ans = -inf
        while i < n - 1:
            j = i + 1
            cur = nums[i]
            while j < n - 1 and nums[j - 1] > nums[j]:
                cur += nums[j]
                j += 1
            if j - i > 1:
                # 計算兩邊的總和
                ans = max(ans, pre[i] + cur + suf[j - 1] - nums[i] - nums[j - 1])
            i = j
        return ans