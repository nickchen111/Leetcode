# TC:O(n) 不計入預處理時間 SC:O(U)
MAX_NUM = 100001
divisors = [[] for _ in range(MAX_NUM)]
divisors_sum = [0] * MAX_NUM
for i in range(1, MAX_NUM):
    for j in range(1, isqrt(i) + 1):
        if i % j == 0:
            if i // j != j:
                divisors[i].append(i // j)
            divisors[i].append(j)
    if len(divisors[i]) == 4:
        divisors_sum[i] = sum(divisors[i])
class Solution:
    def sumFourDivisors(self, nums: List[int]) -> int:
        ans = 0
        for x in nums:
            if divisors_sum[x]:
                ans += divisors_sum[x]
        return ans
