class Solution:
    def sortPermutation(self, nums: List[int]) -> int:
        '''
        只有當兩個數值可以and == k 才可以翻轉 問說k可以多大 可以翻轉數組變成遞增
        '''
        n = len(nums)
        ans = inf
        for i in range(n):
            if nums[i] != i:
                if ans == inf:
                    ans = nums[i]
                    continue
                ans &= nums[i]
        return ans if ans != inf else 0