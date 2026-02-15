# TC:O(n) SC:O(n)
class Solution:
    def firstUniqueFreq(self, nums: List[int]) -> int:
        cnt = Counter(nums)
        st = Counter(cnt.values())
        for x in nums:
            if st[cnt[x]] == 1:
                return x
        return -1
