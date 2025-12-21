class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        '''
        5, 1 如果沒有超過一半 就直接 (tot + 1) // 2
        超過的話-> 超過的數字 - (總數 - 超過數字) + (總數 - 超過數字)
        '''
        n = len(nums)
        cnt1 = Counter(nums)
        cnt2 = Counter(forbidden)
        for x in cnt1:
            if n - cnt2[x] < cnt1[x]:
                return -1
        tot_invalid_cnt = 0
        invalid_cnt = defaultdict(int)
        for x, invalid_x in zip(nums, forbidden):
            if x == invalid_x:
                invalid_cnt[x] += 1
                tot_invalid_cnt += 1
        if tot_invalid_cnt == 0:
            return 0
        max_invalid = max(invalid_cnt.values())
        if max_invalid * 2 <= tot_invalid_cnt:
            return (tot_invalid_cnt + 1) // 2
        return max_invalid
        