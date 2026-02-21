# Math TC:O(logright * logright / loglogright) 因為質數密度計算會是logright/loglogright, SC:O(1)
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
# 數位DP TC:O(logright * logright) SC:O(logright * logright)
prime = {2, 3, 5, 7, 11, 13, 17, 19}
class Solution:
    def countPrimeSetBits(self, left: int, right: int) -> int:

        def solve(x: int) -> int:
            bits = list(map(int, bin(x)[2:]))
            n = len(bits)

            @cache
            def dfs(i: int, cnt1: int, is_limit: bool) -> int:
                if i == n:
                    return 1 if cnt1 in prime else 0

                upper = bits[i] if is_limit else 1
                ans = 0
                for d in range(upper + 1):
                    ans += dfs(i + 1, cnt1 + d, is_limit and d == upper)
                return ans

            return dfs(0, 0, True)

        return solve(right) - solve(left - 1)
