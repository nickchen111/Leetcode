class Solution:
    def specialTriplets(self, nums: List[int]) -> int:
        '''
        計算前後有多少個目前這個數字*2
        '''
        pre, suf = defaultdict(int), defaultdict(int)
        ans = 0
        for x in nums:
            suf[x] += 1
        for x in nums:
            suf[x] -= 1
            ans += pre[x * 2] * suf[x * 2]
            pre[x] += 1
        return ans % (10 ** 9 + 7)