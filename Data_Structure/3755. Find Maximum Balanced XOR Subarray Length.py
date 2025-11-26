# TC:O(n) SC:O(n)
class Solution:
    def maxBalancedSubarray(self, nums: List[int]) -> int:
        '''
        目前odd, even 組合 對應到的 xor 是多少 出現位置 <(x, y), mp<xor, int>>
        '''
        mp = {}
        mp[(0,0)] = -1
        odd = even = ans = 0
        xor_sum = 0
        for i, x in enumerate(nums):
            if x % 2:
                odd += 1
            else:
                even += 1
            xor_sum ^= x
            diff = odd - even
            if (diff, xor_sum) in mp:
                ans = max(ans, i - mp[(diff, xor_sum)])
                continue
            
            mp[(diff, xor_sum)] = i
        return ans
        
