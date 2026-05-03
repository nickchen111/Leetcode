MX = 1001
is_prime = [0, 0] + [1] * (MX - 2)
for i in range(2, isqrt(MX) + 1):
    if is_prime[i]:
        for j in range(i * i, MX, i):
            is_prime[j] = 0

for i in range(1, MX):
    is_prime[i] = is_prime[i - 1] + (i if is_prime[i] else 0)

class Solution:
    def sumOfPrimesInRange(self, n: int) -> int:
        r = 0
        x = n
        while x > 0:
            r = r * 10 + x % 10
            x //= 10
        return is_prime[max(n, r)] - is_prime[min(n, r) - 1]