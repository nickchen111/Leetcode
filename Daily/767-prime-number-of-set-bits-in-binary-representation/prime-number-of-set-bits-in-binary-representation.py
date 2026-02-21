primes = {2, 3, 5, 7, 11, 13, 17, 19}
class Solution:
    def cal(self, high:int) -> int:
        high += 1
        ans = ones = 0
        for i in range(high.bit_length() - 1, -1, -1):
            if high >> i & 1 == 0:
                continue
            # 假設這裡填0 後面都可以亂填, 問題變成在i位中選k個1 讓 ones + k 為質數
            for p in primes:
                k = p - ones
                if k > i:
                    break
                if k >= 0:
                    ans += comb(i, k)
            ones += 1
        return ans
    def countPrimeSetBits(self, left: int, right: int) -> int:
        return self.cal(right) - self.cal(left - 1)



        
       