# TC:O(n + 預處理nloglogn) SC:O(n)
MAX_NUMBER = 10 ** 5 + 1
is_prime = [False] * 2 + [True] * (MAX_NUMBER - 2)
for i in range(2, int(MAX_NUMBER ** 0.5) + 1):
    if not is_prime[i]:
        continue
    for j in range(i * i, MAX_NUMBER, i):
        is_prime[j] = False
class Solution:
    def splitArray(self, nums: List[int]) -> int:
        ans = 0
        for i, x in enumerate(nums):
            ans += x if is_prime[i] else -x
        return abs(ans)
            
