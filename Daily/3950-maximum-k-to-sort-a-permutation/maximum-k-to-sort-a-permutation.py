class Solution:
    def sortPermutation(self, nums: List[int]) -> int:
        '''
        只有當兩個數值可以and == k 才可以翻轉 問說k可以多大 可以翻轉數組變成遞增
        '''
        if nums[0] != 0:
            return 0
        n = len(nums)
        ans = -1
        for i in range(n):
            if i != nums[i]:
                ans &= nums[i]
        return max(ans, 0)