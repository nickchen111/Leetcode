MAX_NUMBER = 10 ** 6 + 1
is_prime = [False] * 2 + [True] * (MAX_NUMBER - 2)
for i in range(2, int(MAX_NUMBER ** 0.5) + 1):
    if is_prime[i]:
        for j in range(i * i, MAX_NUMBER, i):
            is_prime[j] = False
class Solution:
    def minJumps(self, nums: List[int]) -> int:
        n = len(nums)
        mx = max(nums)
        num_to_indices = defaultdict(list)
        for i, num in enumerate(nums):
            num_to_indices[num].append(i)

        visited = [False] * n
        used_primes = set()
        q = deque()
        q.append(0)
        visited[0] = True
        steps = 0

        while q:
            for _ in range(len(q)):
                i = q.popleft()
                if i == n - 1:
                    return steps
                if i + 1 < n and not visited[i + 1]:
                    visited[i + 1] = True
                    q.append(i + 1)

                if i - 1 >= 0 and not visited[i - 1]:
                    visited[i - 1] = True
                    q.append(i - 1)

                val = nums[i]
                if is_prime[val] and val not in used_primes:
                    for j in range(val, mx + 1, val):
                        if j in num_to_indices:
                            for k in num_to_indices[j]:
                                if not visited[k]:
                                    visited[k] = True
                                    q.append(k)
                            del num_to_indices[j]
                    used_primes.add(val)
            steps += 1

        return -1