class Solution:
    def makeTheIntegerZero(self, num1: int, num2: int) -> int:
        '''
        就是要把num1拆解成最少的 num2 + 2 ^ i 最少可以怎拆
        DP!? 
        有正有負 情況比較複雜 DP來做數值範圍太大了感覺會爆
        數學拆解?! num1 = k * num2 + sum(k 個 2 ^ i)
        num1 - k * num2 = sum(k 個 2 ^ i) 
        num1 - k * num2 >= 0
        bit_count(num1 - k * num2) <= k <= num1 - k * num2 (全部都選2 ^ 0)
        那當然會選最少的bit_count()
        '''
        for k in range(1, 61):
            t = num1 - k * num2
            if t < 0:
                continue
            if t.bit_count() <= k <= t:
                return k
        return -1