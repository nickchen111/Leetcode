class Solution:
    def maximumLength(self, nums: List[int]) -> int:
        '''
        LIS odd or even 好像可以直接貪心 
        '''
        n = len(nums)
        one = zero = one_zero = zero_one = 0
        turn_one = turn_zero = True
        for x in nums:
            x %= 2
            one += 1 if x else 0
            zero += 1 if x == 0 else 0
            if x and turn_one:
                one_zero += 1
                turn_one = False
            elif x == 0 and not turn_one:
                one_zero += 1
                turn_one = True
            if x == 0 and turn_zero:
                zero_one += 1
                turn_zero = False
            elif x and not turn_zero:
                zero_one += 1
                turn_zero = True
        # 0, 0 -> even, 0, 1 -> odd, 1, 1 -> even
        return max(one, zero, one_zero, zero_one)
