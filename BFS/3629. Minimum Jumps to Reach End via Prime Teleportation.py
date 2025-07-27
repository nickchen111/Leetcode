# 1st TC:O(nlogU) SC:O(n)
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

# 2nd TC:O(nlogU) SC:O(n)
MX = 10 ** 6 + 1
PRIME_FACTORS = [[] for _ in range(MX)]
for i in range(2, MX):
    if not PRIME_FACTORS[i]:
        for j in range(i, MX, i):
            PRIME_FACTORS[j].append(i)
class Solution:
    def minJumps(self, nums: List[int]) -> int:
        n = len(nums)
        groups = defaultdict(list) # 每個質數可以跳去哪些地方
        for i, x in enumerate(nums):
            for p in PRIME_FACTORS[x]:
                groups[p].append(i) # prime -> list(pos)
        q = [0]
        ans = 0
        vis = [False] * n
        vis[0] = True

        while True:
            tmp = q
            q = []
            for i in tmp:
                if i == n - 1:
                    return ans
                idx = groups[nums[i]]
                idx.append(i + 1)
                if i:
                    idx.append(i - 1)
                for j in idx:
                    if not vis[j]:
                        q.append(j)
                        vis[j] = True
                idx.clear()
            ans += 1
        return -1
