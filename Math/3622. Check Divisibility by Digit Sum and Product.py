# TC:O(n) n 為該數字十進制長度 SC:O(1) 
class Solution:
    def checkDivisibility(self, n: int) -> bool:
        x = n
        sum1 = 0
        sum2 = 1
        while x:
            x, d = divmod(x, 10)
            sum1 += d
            sum2 *= d
            # x //= 10
        return n % (sum1 + sum2) == 0
