class Solution:
    def findXSum(self, nums: List[int], k: int, x: int) -> List[int]:
        n = len(nums)
        i = 0
        ans = []
        mp = defaultdict(int)
        for j in range(n):
            mp[nums[j]] += 1
            pq = []
            if j - i + 1 == k:
                tot = 0
                for key, v in mp.items():
                    heappush(pq, (-v, -key))
                cnt = x
                while pq and cnt > 0:
                    cnt -= 1
                    key, v = heappop(pq)
                    tot += key * v
                ans.append(tot)
                mp[nums[i]] -= 1
                i += 1
        return ans

