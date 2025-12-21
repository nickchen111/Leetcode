# TC:O(krn) SC:O(kr) kr=9
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        k = 3
        MOD = 3
        f = [[-inf] * MOD for _ in range(k + 1)]

        f[0][0] = 0
        for x in nums:
            for j in range(k - 1, -1, -1):
                for r in range(MOD):
                    f[j + 1][(r + x) % MOD] = max(f[j + 1][(r + x) % MOD], f[j][r] + x)
        return max(f[k][0], 0)


# 投機做法
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        # 3 -> 1, 1, 1 or 0, 1, 2, or 0, 0, 0 or 2, 2, 2
        mp = defaultdict(list)
        for i in range(n):
            mp[nums[i] % 3].append(nums[i])
        for k, v in mp.items():
            v.sort()
        cand1 = mp[1][-1] + mp[1][-2] + mp[1][-3] if len(mp[1]) >= 3 else 0
        cand2 = mp[0][-1] + mp[1][-1] + mp[2][-1] if len(mp[0]) >= 1 and len(mp[1]) >= 1 and len(mp[2]) >= 1 else 0
        cand3 = mp[0][-1] + mp[0][-2] + mp[0][-3] if len(mp[0]) >= 3 else 0
        cand4 = mp[2][-1] + mp[2][-2] + mp[2][-3] if len(mp[2]) >= 3 else 0
        return max(cand1, cand2, cand3, cand4)
