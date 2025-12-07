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
