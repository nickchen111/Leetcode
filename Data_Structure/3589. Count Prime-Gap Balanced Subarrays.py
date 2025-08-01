# TC:O(n + U * lglgU) SC:O(U + n)
BASE = 50000
is_prime = [False, False] + [True] * (BASE - 1)
for i in range(2, int(BASE ** 0.5) + 1):
    if is_prime[i]:
        for j in range(i * i, BASE + 1, i):
            is_prime[j] = False
class Solution:
    def primeSubarray(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = left = 0
        # prime_positions = deque() # 或者可以寫直接紀錄後兩個位置的參數
        last = last2 = -1
        max_q = deque()
        min_q = deque()
        for r, x in enumerate(nums):
            if is_prime[x]:
                # prime_positions.append(r)
                last2 = last
                last = r
                while max_q and nums[max_q[-1]] < x:
                    max_q.pop()
                max_q.append(r)
                while min_q and nums[min_q[-1]] > x:
                    min_q.pop()
                min_q.append(r)
                while nums[max_q[0]] - nums[min_q[0]] > k:
                    # l = prime_positions.popleft() + 1
                    left += 1
                    while max_q and max_q[0] < left:
                        max_q.popleft()
                    while min_q and min_q[0] < left:
                        min_q.popleft()
            ans += last2 - left + 1  
        return ans
