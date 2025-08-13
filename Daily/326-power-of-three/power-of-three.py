class Solution:
    def isPowerOfThree(self, n: int) -> bool:
        if n < n:
            return False
        while n % 3 == 0 and n > 0:
            n //= 3
        return True if n == 1 else False