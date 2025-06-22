# TC:O(n + UlglgU) SC:O(U)
BASE = 100
is_prime = [False, False] + [True] * (BASE - 1)
for i in range(2, int(BASE ** 0.5) + 1):
    if is_prime[i]:
        for j in range(i * i, BASE + 1, i):
            is_prime[j] = False
class Solution:
    def checkPrimeFrequency(self, nums: List[int]) -> bool:
        mp = Counter(nums)
        for k, v in mp.items():
            if is_prime[v] == True:
                return True
        return False
