# TC:O(n) n 為該數字十進制長度 SC:O(1) 
class Solution:
    def checkDivisibility(self, n: int) -> bool:
        x = n
        sum1 = 0
        sum2 = 1
        while x:
            cur = x % 10
            sum1 += cur
            sum2 *= cur
            x //= 10
        return n % (sum1 + sum2) == 0
