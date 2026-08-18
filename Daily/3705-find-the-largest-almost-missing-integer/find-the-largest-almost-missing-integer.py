class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        mp = defaultdict(int)
        mp2 = defaultdict(int)
        n = len(nums)
        i = 0
        for j in range(n):
            mp[nums[j]] += 1
            if j - i + 1 == k:
                for key,v in mp.items():
                    mp2[key] += 1
                mp[nums[i]] -= 1
                if mp[nums[i]] == 0:
                    del mp[nums[i]]
                i += 1
        ans = -1
        for key, v in mp2.items():
            if v == 1:
                ans = max(ans, key)
        return ans