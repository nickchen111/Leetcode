# TC:O(logn * sqrt(M)) M 為n的大小 SC:O(1)
class Solution:
    def completePrime(self, num: int) -> bool:
        s = str(num)
        if s[0] == '1' or s[-1] == '1':
            return False
        tmp = 0
        for ch in s:
            tmp = tmp * 10 + int(ch)
            for j in range(2, isqrt(tmp) + 1):
                if tmp % j == 0:
                    return False
        n = len(s)
        tmp = 0
        cnt = 1
        for i in range(n - 1, -1, -1):
            tmp = tmp + int(s[i]) * cnt
            cnt *= 10
            for j in range(2, isqrt(tmp) + 1):
                if tmp % j == 0:
                    return False
        return True
            
