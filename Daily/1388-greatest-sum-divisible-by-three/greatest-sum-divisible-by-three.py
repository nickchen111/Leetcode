class Solution:
    def maxSumDivThree(self, nums: List[int]) -> int:
        mp = [-1] * 3
        for x in nums:
            mod = x % 3
            tmp = [-1] * 3
            for i in range(0, 3):
                if mp[i] != -1:
                    tmp[(i + mod) % 3] = max(mp[i] + x, tmp[(i + mod) % 3])
            tmp[mod] = max(tmp[mod], x)
            for i in range(0, 3):
                mp[i] = max(tmp[i], mp[i])
            # print(mp)
        return mp[0] if mp[0] != -1 else 0
