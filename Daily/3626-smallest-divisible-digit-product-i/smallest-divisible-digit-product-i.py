class Solution:
    def smallestNumber(self, n: int, t: int) -> int:
        cur = n
        while True:
            tmp = cur
            num = 1
            while tmp:
                x, d = divmod(tmp,10)
                num *= d
                tmp = x
            if num % t == 0:
                return cur
            cur += 1
        return -1