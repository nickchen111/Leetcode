# TC:O(n) SC:O(n)
max = lambda a, b: b if b > a else a
class Solution:
    def findLHS(self, nums: List[int]) -> int:
        mp = Counter(nums)
        ans = 0
        for k, cnt in mp.items():
            if k + 1 in mp:
                ans = max(ans, cnt + mp[k + 1])
        return ans
