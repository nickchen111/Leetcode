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

