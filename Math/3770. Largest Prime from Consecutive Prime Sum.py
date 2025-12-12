# TC:O(UlogU 預處理 + logn) SC:O(1)
MX = 500_000

is_prime = [False] * 2 + [True] * (MX - 1)
primes = []
for i in range(2, MX + 1):
    if is_prime[i]:
        primes.append(i)
        for j in range(i * i, MX + 1, i):
            is_prime[j] = False

special_primes = [0]
sum_p = 0
for p in primes:
    sum_p += p
    if sum_p > MX:
        break
    if is_prime[sum_p]:
        special_primes.append(sum_p)


class Solution:
    def largestPrime(self, n: int) -> int:
        i = bisect_right(special_primes, n) - 1
        return special_primes[i]

# 笨一點的方法

MAX_NUMBER = 5 * 10 ** 5 + 1
is_prime = [False] * 2 + [True] * (MAX_NUMBER - 2)
for i in range(2, int(MAX_NUMBER ** 0.5) + 1):
    if not is_prime[i]:
        continue
    for j in range(i * i, MAX_NUMBER, i):
        is_prime[j] = False
class Solution:
    def largestPrime(self, n: int) -> int:
        # 找出目前這個數字有哪些質數
        arr = []
        ans = 0
        m = n
        while m:
            if is_prime[m]:
                arr.append(m)
            m -= 1
        # 使用質數
        arr.sort()
        cur = 0
        for x in arr:
            cur += x
            if cur > n:
                break
            if is_prime[cur]:
                ans = cur
        return ans
