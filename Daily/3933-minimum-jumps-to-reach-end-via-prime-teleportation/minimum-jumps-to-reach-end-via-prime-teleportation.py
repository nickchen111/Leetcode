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
